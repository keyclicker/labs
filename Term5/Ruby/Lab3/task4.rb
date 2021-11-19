puts "Input x:"
x = gets.to_i

DIF = 0.00001

def fac(n)
  n > 1 ? n * fac(n - 1) : 1
end

def subtask1
  n, sum, cur = 2, 0.0, 1
  while cur > DIF
    cur = (fac(n - 1.0) / fac(n + 1.0)) ** (n * (n + 1))
    sum += cur
    n += 1
  end
  [sum, n - 1]
end

sum, n = subtask1
puts "Subtask 1:"
puts "\tResult: #{sum}"
puts "\tNumber of iterations: #{n - 1}"


# Subtask 2
def mycos(x)
  n, sum, cur = 0, 0.0, 1
  while cur.abs > DIF
    cur = (-1) ** n * x ** (2.0 * n) / fac(2.0 * n)
    sum += cur
    n += 1
  end
  [sum, n - 1]
end

sum, n = mycos(x)
puts "\nSubtask 2:"
puts "\tMath.cos(x): #{Math.cos(x)}"
puts "\tResult: #{sum}"
puts "\tNumber of iterations: #{n - 1}"


# Subtask 3
def subtask3(x)
  n, sum, cur = 0, 0.0, 1
  while cur.abs > DIF
    cur = fac(3.0 * n - 2) * fac(2.0 * n - 1) /
      (fac(4.0 * n) * 5.0 ** (2 * n) * fac(2.0 * n))
    sum += cur
    n += 1
  end
  [sum, n - 1]
end

sum, n = subtask3(x)
puts "\nSubtask 3:"
puts "\tResult: #{sum}"
puts "\tNumber of iterations: #{n - 1}"