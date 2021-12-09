import mysql.connector
import Pyro4

db = mysql.connector.connect(
    host="localhost",
    user="root",
    password="password",
    database="airport"
)

cursor = db.cursor(buffered=True)
cursor.execute("SHOW DATABASES")

def fetch(query):
    cursor.execute(query)
    return cursor.fetchall()


def commit(query):
    try:
        cursor.execute(query)
        db.commit()
    except Exception as e:
        db.rollback()
        raise e


@Pyro4.expose
class Database:
    def get_airlines(self):
        return fetch("select * from airlines")


    def get_flights(self):
        return fetch("select * from flights")


    def get_airline_flights(self, id_a):
        return fetch("select * from flights where id_a = %d" % id_a)


    def get_airline(self, id_a):
        res = fetch("select * from airlines where id_a = %d" % id_a)
        return res[0] if len(res) == 1 else None


    def get_flight(self, id_f):
        res = fetch("select * from flights where id_f = %d" % id_f)
        return res[0] if len(res) == 1 else None


    def add_airline(self, id_a, name, city):
        commit("insert into airlines "
               "values (%d, '%s', '%s')" % (id_a, name, city))


    def add_flight(self, id_f, id_a, _from, to):
        commit("insert into flights "
               "values (%s, '%s', '%s', '%s')" % (str(id_f), id_a, _from, to))


    def update_airline(self, id_a, name, city):
        commit("update airlines "
               "set name = '%s', city = '%s' "
               "where  id_a = %d" % (name, city, id_a))


    def update_flight(self, id_f, _from, to):
        commit("update flights "
               "set `from` = '%s', `to` = '%s' "
               "where id_f = %d" % (_from, to, id_f))


    def remove_airline(self, id_a):
        commit("delete from airlines "
               "where id_a = %d" % id_a)


    def remove_flight(self, id_f):
        commit("delete from flights "
               "where id_f = %d" % id_f)


    def print_airline(self, row):
        print("%d: name=\"%s\" city=\"%s\"" % row)


    def print_flight(row):
        print("%d: airline=\"%s\" from=\"%s\" city=\"%s\"" % row)


    def print_airlines(airlines):
        for row in airlines:
            print_airline(row)


    def print_flights(flights):
        for row in flights:
            print_flight(row)


