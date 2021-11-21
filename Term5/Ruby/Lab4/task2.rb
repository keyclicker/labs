require 'matrix'
require_relative 'print'

# @param [Matrix] _a
# @param [Array] _b
def gauss(_a, _b)
  a, b = _a.dup, _b.dup
  size = a.row_size

  (0...size - 1).each do |i|
    (i + 1...size).each do |j|
      ratio = a[j, i] / a[i, i]
      b[j] -= ratio * b[i]
      (0...size).each do |k|
        a[j, k] -= ratio * a[i, k]
      end
    end
  end

  res = Array.new(size, 0)

  (0...size).reverse_each do |i|
    res[i] = b[i]
    (i + 1...size).each do |j|
      res[i] -= a[i, j] * res[j]
    end
    res[i] /= a[i, i]
  end
  res
end

puts "Input n:"
n = gets.to_i

a = Matrix.build(n, n) { |x, y| x == y ? 2.0 : 15.0 }

b = []
(0...n).each do |i|
  b.push(i.to_f)
end


Print.matrix(a, b)

s = gauss(a, b)
printf("\nSolutions = ["+ "%0.2f, " * (s.size - 1) + "%0.2f]\n", *s)