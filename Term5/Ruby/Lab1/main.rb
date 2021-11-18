def fun(a, z, x, p)
  (Math.log(z.abs) * Math.sin(p) ** 0.5) /
    (a + Math.sqrt(Math.tan(x)**2)) +
    1.3 * 10 ** (-1.6) * Math.sqrt(z + x) + Math::E ** Math::PI
end

puts "Input a, z, x, p"
a, z, x, p = gets.chomp.split.map { |i| i.to_i }

puts "l = #{fun(a, z, x, p)}"