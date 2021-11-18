p, t, r = 2, 16, 8

range = p ** r * (1 - p ** -t).round

puts "range: #{range}"