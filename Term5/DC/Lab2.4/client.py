import Pyro4

ns = Pyro4.locateNS()
uri = ns.lookup("db")
o = Pyro4.Proxy(uri)


def _exec(pref, fun, *args):
    print(pref, args, ":", fun(*args))


_exec("add_airline", o.add_airline, 50, "Name", "City")
_exec("add_flight", o.add_flight, 98, 50, "From", "To")

print()
_exec("update_airline", o.update_airline, 50, "Edited Name", "City")
_exec("update_flight", o.update_flight, 98, "From", "To EDIT")

print()
_exec("get_airline", o.get_airline, 50)
_exec("get_flight", o.get_flight, 98)

print()
_exec("remove_airline", o.remove_airline, 50)
_exec("remove_flight", o.remove_flight, 98)

print()
_exec("get_airlines", o.get_airlines)
_exec("get_flights", o.get_flights)
