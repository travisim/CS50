-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = "Chamberlin Street";

--description
Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

SELECT interviews.name, interviews.transcript FROM interviews WHERE day = 28 AND month = 7;

Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
--10 min after crime exit carpark
Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
--before at ATM Fifer Street withdrawing
Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
--after leave courthouse,call less than 1 min earliest flight purchase tickets


------------------------------------------------------------FROM raymond

SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND duration <= 60;
221 | (130) 555-0289 | (996) 555-8899 | 2020 | 7 | 28 | 51
224 | (499) 555-9472 | (892) 555-8872 | 2020 | 7 | 28 | 36
233 | (367) 555-5533 | (375) 555-8161 | 2020 | 7 | 28 | 45
251 | (499) 555-9472 | (717) 555-1342 | 2020 | 7 | 28 | 50
254 | (286) 555-6063 | (676) 555-6554 | 2020 | 7 | 28 | 43
255 | (770) 555-1861 | (725) 555-3243 | 2020 | 7 | 28 | 49
261 | (031) 555-6622 | (910) 555-3251 | 2020 | 7 | 28 | 38
279 | (826) 555-1652 | (066) 555-9701 | 2020 | 7 | 28 | 55
281 | (338) 555-6650 | (704) 555-2131 | 2020 | 7 | 28 | 54

SELECT name FROM people where phone_number IN (SELECT caller FROM phone_calls WHERE day = 28 AND month = 7 AND duration < 60);
Bobby
Roger
Victoria
Madison
Russell++
Evelyn
Ernest++
Kimberly
SELECT name FROM people where phone_number IN (SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND duration < 60);
James
Larry
Anna
Jack
Melissa
Jacqueline
Philip
Berthold
Doris . ----

SELECT * FROM flights WHERE day = 29 AND month = 7;
8 | 8 | 4 | 36
SELECT id FROM flights WHERE day = 29 AND month = 7 ORDER BY hour;
36
43
23
53
18

SELECT origin_airport_id, destination_airport_id,id FROM flights WHERE day = 29 AND month = 7 AND hour IN(SELECT MIN(hour)FROM flights WHERE day = 29 AND month = 7);
8 | 4 | 36
SELECT name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE flights.day = 29 AND flights.month = 7 AND flights.hour IN(SELECT MIN(hour)FROM flights WHERE day = 29 AND month = 7);
Doris
Roger
Ernest
Edward
Evelyn
Madison
Bobby
Danielle



SELECT name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.caller IN (SELECT phone_number FROM people where name = "Ernest") AND day = 28 AND month = 7 AND duration < 60
Berthold
------------------------------------------------------------FROM RUTH


SELECT license_plate FROM courthouse_security_logs where day = 28 AND month = 7 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit";
5P2BI95
94KL13X
6P58WS2
4328GD8
G412CB7
L93JTIZ
322W7JE
0NTHK55
SELECT * FROM people
WHERE  people.license_plate IN (SELECT license_plate FROM courthouse_security_logs where day = 28 AND month = 7 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit");

221103 | Patrick | (725) 555-4692 | 2963008352 | 5P2BI95
243696 | Amber | (301) 555-4174 | 7526138472 | 6P58WS2
396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
SELECT name FROM people
WHERE  people.license_plate IN (SELECT license_plate FROM courthouse_security_logs where day = 28 AND month = 7 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit");
Patrick
Amber
Elizabeth
Roger
Danielle
Russell
Evelyn
Ernest
------------------------------------------------------------FROM eugene

SELECT atm_transactions.account_number, atm_transactions.atm_location, atm_transactions.transaction_type, atm_transactions.amount
FROM atm_transactions
WHERE atm_location = "Fifer Street"AND day = 28 AND month = 7 AND transaction_type = 'withdraw';

28500762 | Fifer Street | withdraw | 48
28296815 | Fifer Street | withdraw | 20
76054385 | Fifer Street | withdraw | 60
49610011 | Fifer Street | withdraw | 50
16153065 | Fifer Street | withdraw | 80
25506511 | Fifer Street | withdraw | 20
81061156 | Fifer Street | withdraw | 30
26013199 | Fifer Street | withdraw | 35

SELECT bank_accounts.account_number, people.name, people.phone_number,people.passport_number,people.license_plate
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number IN (SELECT atm_transactions.account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7);

49610011 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X ------
86363979 | Robert | (098) 555-1164 | 8304650265 | I449449
26013199 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
16153065 | Roy | (122) 555-4581 | 4408372428 | QX4YZN3
28296815 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
25506511 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
28500762 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
76054385 | Madison | (286) 555-6063 | 1988161715 | 1106N58
81061156 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0

SELECT name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number IN (SELECT atm_transactions.account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7);


------------------------------------------------------------FROM eugene+ruth






SELECT name FROM people
WHERE  people.license_plate IN (SELECT license_plate FROM courthouse_security_logs where day = 28 AND month = 7 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit") AND name IN(
SELECT  people.name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number IN (SELECT atm_transactions.account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = 28 AND month = 7));
Elizabeth
Danielle
Russell
Ernest

Select city FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE flights.id = 36;
London



car
    Patrickx
    Amberx
    Elizabethx
    Rogerx
    Daniellex
    Russell
    Evelynx
    Ernest  -----



Russel or ernest

caller
    Bobby
    Roger
    Victoria
    Madison
    Russell
    Evelyn
    Ernest
    Kimberly

money
    Ernest
    Robert
    Russell
    Roy
    Bobby
    Elizabeth
    Danielle
    Madison
    Victoria
flyers
    Doris
Roger
Ernest
Edward
Evelyn
Madison
Bobby
Danielle