puts "Input x, n:"
x, n = gets.split(' ').map { |s| s.to_i }

def subtask1(x)
  res = 1.0
  (1..10).each do |i|
    res += (i + 1.0) / (i + 2.0) * x ** i * (i.even? ? 1 : -1)
  end
  res
end

puts "Subtask 1: #{subtask1(1)}"


def subtask2
  res = 1.0
  (1..8).each do |i|
    res += 1.0 / 3 ** i
  end
  res
end

puts "Subtask 2: #{subtask2}"


def subtask3(x, n)
  res = 1.0
  fac = 1.0
  (1..n).each do |i|
    fac *= i
    res += x ** i / fac
  end
  res
end

puts "Subtask 3: #{subtask3(x, n)}"


def subtask4(n)
  res = 1.0
  sin_sum = 0
  (1..n).each do |i|
    sin_sum += Math.sin(i)
    res += 1.0 / sin_sum
  end
  res
end

puts "Subtask 4: #{subtask4(n)}"


def subtask5(n)
  res = 0
  (1..n).each do
    res = Math.sqrt(res + 2)
  end
  res
end

puts "Subtask 5: #{subtask5(n)}"