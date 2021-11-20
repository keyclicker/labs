# variant 15 % 12 = 3

def intersection(a, b)
  res = []
  a.each do |i|
    b.each do |j|
      if i == j
        res.push(i)
      end
    end
  end
  res
end

a = [1, 5, 3, 6, 10, 50, 0, 4, 58, 42]
b = [54, 98, 1, 6, 42, 50, 4, 0, 15, 22]
puts "a = #{a.to_s}"
puts "a = #{b.to_s}"
puts "a ∩ b = #{intersection(a, b)}"
