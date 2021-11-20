require 'matrix'

# @param [Matrix] m
def printm(m)
  maxw = 0
  m.each do |i|
    maxw = [i.to_s.size, maxw].max
  end

  format = "│" + " %#{maxw}i" * m.row_size + " │\n"
  m.to_a.each do |r|
    printf(format, *r)
  end
end

# @param [Matrix] m
def trace(m)
  unless m.square?
    raise "Matrix sould be square"
  end

  sum = 0
  (0...m.row_size).each do |i|
    sum += m[i, i]
  end
  sum
end

b = Matrix.build(8, 8) { rand(10) }

puts "\nB ="
printm b

puts "\nb.trace = #{b.trace}"
puts "trace(m) = #{trace(b)}"