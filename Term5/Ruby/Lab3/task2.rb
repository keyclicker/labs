def y(x)
  x = x.to_f
  if x > -4 && x <= 0
    ((x - 2).abs / (x ** 2 * Math.cos(x))) ** (1 / 7.0)
  elsif x > 0 && x <= 12
    1 / (Math.tan(x + Math.exp(-x)) / Math.sin(x) ** 2) ** (7 / 2.0)
  elsif x < -4 || x > 12
    1 / (1 + x / (1 + x / (1 + x)))
  end
end

puts "Input x:"
x = gets.to_i

puts y(x)
