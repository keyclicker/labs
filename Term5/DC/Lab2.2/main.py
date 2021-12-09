from database import Database


def print_airline(row):
    print("%d: name=\"%s\" city=\"%s\"" % row)


def print_flight(row):
    print("%d: airline=\"%s\" from=\"%s\" city=\"%s\"" % row)


def print_airlines(airlines):
    for row in airlines:
        print_airline(row)


def print_flights(flights):
    for row in flights:
        print_flight(row)


def print_demo(_db):
    print("All Airlines:")
    print_airlines(_db.get_airlines())

    print("\nAll Flights:")
    print_flights(_db.get_flights())

    print("\nAll Flights of airline with id = 25:")
    print_flights(_db.get_airline_flights(25))

    print("\nAirline with id = 1:")
    print_airline(_db.get_airline(1))

    print("\nFlight with id = 3:")
    print_flight(_db.get_flight(3))

    print("\n\n")


_db = Database()

print_demo(_db)
_db.add_airline(25, "test", "testtt")
_db.add_flight(20, 25, "Kyiv", "Lviv")
_db.update_flight(2, "updated", "updated")
_db.update_airline(3, "updated", "updated")
print_demo(_db)

_db.remove_flight(25)
_db.remove_flight(20)


