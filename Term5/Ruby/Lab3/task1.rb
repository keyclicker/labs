# Subtask 1

def btoi(b)
  b ? 1 : 0
end

a, b, c = false, false, false
x, y, z = 1, 2, -39

puts !(a || b) && (a && !b)
puts btoi(z != y) <= btoi(6 >= y) && a || b && c && x >= 1.5
puts (8 - x * 2 <= z) && (x ** 2 != y ** 2) || (z >= 15)
puts x > 0 && y < 0 || z >= (x * y + (-y / x)) + (-z) * 3
puts not(a or b and not(c or (not a or b))) # just decided to try this style too
puts x ** 2 + y ** 2 >= 1 && x >= 0 && y >= 0
puts (a && (c && b != b || a) || c) && b
puts

# Subtask 2

m, n = -2, 1
q, p = false, true

puts (p and q) == not(not p or not q) and
  (Math.sqrt(m) + Math.sqrt(n) < 4) and (m + n < 1)