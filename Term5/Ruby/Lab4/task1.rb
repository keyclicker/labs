require 'matrix'
require_relative 'print'

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
Print.matrix b

puts "\nb.trace = #{b.trace}"
puts "trace(m) = #{trace(b)}"