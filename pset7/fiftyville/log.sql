-- Keep a log of any SQL queries you execute as you solve the mystery of the stolen cs50 duck.
-- Find the thief, accomplice, and city they escaped to using the town's records.
-- We know the theft took place on July 28, 2023 on Humphrey Street.

-- Familiarize the database and what information it holds
.tables
.schema

-- Check out the crime_scene_reports table
SELECT * FROM crime_scene_reports;

-- Filter it down to look for our crime
SELECT * FROM crime_scene_reports
WHERE year = 2023
    AND month = 7
    AND day = 28
    AND street = 'Humphrey Street';

-- Notes:
-- id: 295
-- description: Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- Check out the contents of the interviews
.schema
SELECT * FROM interviews
WHERE year = 2023
    AND month = 7
    AND day = 28
    AND transcript LIKE '%bakery%';

-- Notes:
-- Ruth: Within 10mins, thief got into car in bakery parking lot and left. Check security footage.
-- Eugene: Recognized thief, but didn't know name. Before arriving at Emma's bakery, saw thief withdraw money at ATM on Leggett Street.
-- Raymond: As thief left bakery, called accomplice for less than a minute. The thief will take earliest flight out of Fiftyville tomorrow and
--          accomplice will purchase the flight ticket.

-- Use Ruth and Eugene's accounts to identify the thief suspects, Raymond to identify the accomplice and where thief escaped.

-- Check bakery security footage, we know the theft happened at 10:15am.
SELECT * FROM bakery_security_logs
WHERE year = 2023
    AND month = 7
    AND day = 28;

-- List of license plates that exited the bakery between 10:15 and 10:25
SELECT license_plate FROM bakery_security_logs
WHERE year = 2023
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25
    AND activity = 'exit';

-- Check ATM information
.schema
SELECT * FROM atm_transactions
LIMIT 5;

-- Filter to withdrawal at Leggett Street on July 28th
SELECT * FROM atm_transactions
WHERE year = 2023
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw';

-- List of account numbers and amounts that withdrew that day
SELECT account_number, amount FROM atm_transactions
WHERE year = 2023
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw';

-- See if there's any information we can gather about the thief using license plate and bank account
.schema

-- Looks like we can potentially find the thief's person id, thus name using the bank accounts and license plates from the clues eariler. Any overlaps?
SELECT * FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number IN
(
    SELECT account_number FROM atm_transactions
    WHERE year = 2023
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
)
AND license_plate IN
(
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2023
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute >= 15
        AND minute <= 25
        AND activity = 'exit'
);

-- Notes:
-- We have four thief suspects after this: Bruce, Diana, Iman, and Luca, each with a license plate that left the bakery within 10mins after the crime,
-- and a withdrawal at the Leggett Street ATM the same day as the crime. All of their passports are in this table as well. Now onto checking the flight information.

-- Raymond mentioned a call that happened between the thief and their accomplice about airplane tickets. A good place to start.
.schema
SELECT * FROM phone_calls;

-- We know the call was on the same day as the crime and lasted less than a minute. It seems duration is in seconds.
SELECT * FROM phone_calls
WHERE year = 2023
    AND month = 7
    AND day = 28
    AND duration < 60;

-- Notes:
-- We've got a few hits, the caller and receiver numbers are in this table. Can further filter this table using the code above when necessary.

-- Let's look at the flights out of Fiftyville the next day.
.schema
SELECT * FROM flights
WHERE year = 2023
    AND month = 7
    AND day = 29
-- Order by earliest to latest
ORDER BY hour ASC;

-- Now to find the destination airport name of the earliest flight
.schema
SELECT * FROM airports;

-- Notes:
-- Looks like all the flights in the flights log on 7/29 are origin Fiftyville, or airport id 8. The origin/destination id's correspond with the airport
-- id's in the airport table. The earliest flight out is at 8:20 destination id 4, or LaGuardia Airport LGA in New York City.

-- Can we find who purchased the flight ticket?
.schema

-- Not directly it seems, but they're probably the receiver phone number of the thief's call.
-- Let's see who was on the early departing flight to LGA that next morning and if any passport numbers line up with the license plate and bank account info.
-- Looks like a flight id is necessary to identify the correct flight, which corresponds with the id in flights.
SELECT * FROM passengers
JOIN flights ON flights.id = passengers.flight_id
WHERE flights.id =
(
    SELECT id FROM flights
    WHERE year = 2023
        AND month = 7
        AND day = 29
        AND hour = 8
        AND minute = 20
);

-- To get the passport info only replace * with passport_number

-- Check for overlap now with the current suspects and passport number
SELECT * FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number IN
(
    -- Made a withdrawal at Leggett day of crime
    SELECT account_number FROM atm_transactions
    WHERE year = 2023
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
)
AND license_plate IN
(
    -- Left bakery within 10 mins of crime
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2023
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute >= 15
        AND minute <= 25
        AND activity = 'exit'
)
AND passport_number IN
(
    -- Passenger on earliest flight out of Fiftyville next day
    SELECT passport_number FROM passengers
    JOIN flights ON flights.id = passengers.flight_id
    WHERE flights.id =
    (
        SELECT id FROM flights
        WHERE year = 2023
            AND month = 7
            AND day = 29
            AND hour = 8
            AND minute = 20
    )
);

-- Notes:
-- Bruce and Luca! Need to crosscheck phone number with outgoing phonecalls too
SELECT * FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number IN
(
    -- Made a withdrawal at Leggett day of crime
    SELECT account_number FROM atm_transactions
    WHERE year = 2023
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
)
AND license_plate IN
(
    -- Left bakery within 10 mins of crime
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2023
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute >= 15
        AND minute <= 25
        AND activity = 'exit'
)
AND passport_number IN
(
    -- Passenger on earliest flight out of Fiftyville next day
    SELECT passport_number FROM passengers
    JOIN flights ON flights.id = passengers.flight_id
    WHERE flights.id =
    (
        SELECT id FROM flights
        WHERE year = 2023
            AND month = 7
            AND day = 29
            AND hour = 8
            AND minute = 20
    )
)
AND phone_number IN
(
    -- Made a short call on the day of the crime
    SELECT caller FROM phone_calls
    WHERE year = 2023
        AND month = 7
        AND day = 28
        AND duration < 60
);

-- Still Bruce and Luca! Is there a time associated with bank withdrawals? Must be before the crime. Is there any way we could know if Eugene would recognize them?
.schema

-- Let's add names to that call table
SELECT * FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
    WHERE year = 2023
        AND month = 7
        AND day = 28
        AND duration < 60;

-- Phone number in phone_calls table is referenced using caller not phone_number. Fixed in the SQL code above. Bruce is our thief as he is the only suspect
-- with an outgoing call less than a minute that day!
-- But who did he call?

-- Select names of people
SELECT name FROM people
WHERE phone_number IN
(
    -- Select receiver of Bruce's phone call
    SELECT receiver FROM phone_calls
    WHERE caller =
    (
        -- Select Bruce's phone number
        SELECT phone_number FROM people
        WHERE name = 'Bruce'
    )
    -- Bruce has many calls logged, filter for date and duration
    AND year = 2023
    AND month = 7
    AND day = 28
    AND duration < 60
);

-- It was Robin.

-- Quick check of names & phone numbers & calls
-- Name and phone number for reference
SELECT * FROM people
WHERE name = 'Bruce'
OR name = 'Robin';

-- Phone numbers of caller and receiver of Bruce's short call on day of theft
SELECT caller, receiver FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE year = 2023
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller =
    (
        SELECT phone_number FROM people
        WHERE name = 'Bruce'
    );

-- It was indeed Bruce who flew to New York City with the help of Robin.




