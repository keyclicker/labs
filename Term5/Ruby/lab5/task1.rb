# @param [Method] f function
def prm(f, a, b, n)
  h = (b - a) / n.to_f
  res = 2.0
  (1..n).each do |i|
    x = a + i * h - h / 2.0
    res += f.call(x)
  end
  res *= h
end

# @param [Method] f function
def trp(f, a, b, n)
  h = (b - a) / (n.to_f - 1)
  res = f.call(a) / 2.0
  (1...n - 1).each do |i|
    x = a + i * h
    res += f.call(x)
  end
  res = (res + f.call(b) / 2.0) * h
end


def f1(x)
  x ** 3 * Math.exp(2 * x)
end

def f2(x)
  1.0 / (x * Math.log(x) ** 2)
end

# @param [Method] f function
def run(f, a, b, n)
  prm_f1 = prm(f, a, b, n)
  trp_f2 = trp(f, a, b, n)

  puts "f = #{f.name}, a = #{a}, b = #{b}, c = #{n}"
  puts "prm = #{prm_f1}"
  puts "trp = #{trp_f2}"
  puts "Average: #{(prm_f1 + trp_f2) / 2.0}"
  puts
end

n = 256
run(method(:f1), 0.0, 0.8, n)
run(method(:f2), 2.0, 2.5, n)


