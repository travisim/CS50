import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
import time
from helpers import apology, login_required, lookup, usd
import re

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


    
# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")
#--------------------------------------------------------------------------------


@app.route("/")
@login_required
def index():
    holdings = []
    total = 0
    rows = db.execute("""
        SELECT symbol, SUM(shares) as sum_of_shares
        FROM orders
        WHERE user_id = ?
        GROUP BY symbol
        HAVING sum_of_shares > 0;
    """, session["user_id"])
    for i in rows:
        stock = lookup(i["symbol"]) 
        holdings.append({
            "name": stock["name"],
            "symbol": i["symbol"],
            "price": usd(stock["price"]),
            "shares": i["sum_of_shares"],
            "total": usd(stock["price"] * i["sum_of_shares"])
        })
        total += i["sum_of_shares"] * stock["price"] 
    rows = db.execute("SELECT cash FROM users WHERE id = ?",session["user_id"])
    cash = rows[0]["cash"]
    total += cash
    return render_template("index.html", holdings=holdings, cash=usd(cash), total=usd(total))

    


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    
    if request.method == "POST":
     
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        if not request.form.get("shares"):
            return apology("must provide shares", 400)
        elif not request.form.get("shares").isdigit():
            return apology("must provide valid number of shares", 400)
        stock = lookup(request.form.get("symbol").upper())
        shares = int(request.form.get("shares"))
        
        if stock is None:
            return apology("must provide valid symbol",400)
        cash = db.execute("SELECT cash FROM users WHERE id =?", session["user_id"])[0]["cash"]
        
        
        new_cash = cash - stock['price'] * shares
   
       
        if new_cash <= 0:
            return apology("can't afford",400)
        db.execute("UPDATE users SET cash=? WHERE id=?",
                    new_cash,
                    session["user_id"])
        db.execute("""
            INSERT INTO orders(user_id, symbol, shares,price)
            Values(?, ?, ?, ?)
            """,
            session["user_id"],
            stock["symbol"],
            shares,
            stock["price"]
        )
        flash("Stocks bought","sucess")
        return  redirect("/")
    else:
        return render_template("buy.html")
  

@app.route("/history")
@login_required
def history():
    
    orders = db.execute("""
        SELECT symbol, shares, price, transacted
        FROM orders
        WHERE user_id = ?
    """, session["user_id"])
    for i in range(len(orders)):
        orders[i]["price"] = usd(orders[i]["price"])
    return render_template("history.html", orders=orders)
   



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        #Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)
        
        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)
            

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
            
        stock = lookup(request.form.get("symbol").upper())
        if stock is None:
            return apology("invalid symbol", 400)
      
        return render_template("quoted.html", stockName={
            'name': stock['name'],
            'price': usd(stock['price']),
            'symbol': stock['symbol']
        })
    else:
        return render_template("quote.html")
        
        
        

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 400)
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        password = request.form.get("password")
      
        length_error = len(password) < 8
        # searching for digits
        digit_error = re.search(r"\d", password) is None
        
        # searching for uppercase
        uppercase_error = re.search(r"[A-Z]", password) is None
        
        # searching for lowercase
        lowercase_error = re.search(r"[a-z]", password) is None
        
        # searching for symbols
        symbol_error = re.search(r"[ !#$%&'()*+,-./[\\\]^_`{|}~" + r'"]', password) is None
        
        # overall result
        password_ok = not (length_error or digit_error or uppercase_error or lowercase_error or symbol_error)
        
        if password_ok == False:
            return apology("must satisfy password requirements", 400)
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match",400)
        
        try:
            k = db.execute("INSERT INTO users (username,hash) VALUES (?,?)",
            request.form.get("username"),
            generate_password_hash(request.form.get("password")))
                
        
        except:
            return apology("user exists already", 400)
            
        if k is None:
            return apology("registration failed", 403)
        session["user_id"] = k
        return redirect("/")
                
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
     
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)
        elif not request.form.get("shares"):
            return apology("must provide shares", 403)
        elif not request.form.get("shares").isdigit():
            return apology("invalid number of shares", 403)
        shares = int(request.form.get("shares"))
        symbol = request.form.get("symbol").upper()
        stock = lookup(request.form.get("symbol").upper())
        if stock is None:
            return apology("invalid symbol",400)
        
        
        rows = db.execute("""
        SELECT symbol, SUM(shares) as sum_of_shares
        FROM orders
        WHERE user_id = ?
        GROUP BY symbol
        HAVING sum_of_shares > 0;
        """, session["user_id"])
        for i in rows:
            if i["symbol"] == symbol:
                if shares > i["sum_of_shares"]:
                    return apology("too many shares",400)
        
     
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        symbol = request.form.get("symbol").upper()
        new_cash = cash + shares * stock['price']
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                    new_cash,
                    session["user_id"])
        db.execute("""
            INSERT INTO orders(user_id, symbol, shares,price)
            Values( :user_id, :symbol, :shares, :price)
            """,
            user_id=session["user_id"],
            symbol = stock["symbol"],
            shares = -1 * shares,
            price = stock["price"]
        )
        flash("sold","sucess")
        return redirect("/")
    else:
        rows = db.execute("""
            SELECT symbol
            FROM orders
            WHERE user_id = ?
            GROUP BY symbol
            HAVING SUM(shares) > 0;
        
        """, session["user_id"])
        return render_template("sell.html", symbols=[row["symbol"] for row in rows])


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
