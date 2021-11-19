
puts "Input n, c:"
$n, $c = 10, 10
$n, $c = gets.split(' ').map { |s| s.to_i }

def fy(x)
  (4 * x * (x + Math.sqrt(($n - x ** 2 + 1 / $c).abs)) ** ((x - $c) / 2 + x ** (1 / 3))) /
  (x + Math.sqrt(x**2 - 1) ** (4 + 1 / $c) - 1) +
  Math.sqrt((x + 1) **2 + 1) /
  (Math.sqrt(x) + 2 / Math.sqrt(x))
end

def fz(x)
  Math.sin(2 * x) ** 2 -
  Math.cos(Math::PI / 3 - 2 * x) *
  Math.sin(2 * x - Math::PI / 6) -
  1.0 / Math.tan((Math::PI + x) / (x + 1)).abs ** (2 / x)
end

def fun(x)
  fy(x) + fz(x)
end

def tab(st, en, cnt, funs)
  res = []
  (0...cnt).each do |i|
    x = st + (en - st) * i / (cnt - 1).to_f
    row = [x]
    funs.each do |f|
      row.push(f.call(x))
    end
    res.push(row)
  end
  res
end

def print_tab(tab, header)
  w, s = 8, header.size
  headerf = "║ %-#{w}s" * s + "║\n"
  rowsf = "║ %-#{w}.2f" * s + "║\n"

  l = "═" * (w + 1)
  puts "╔" + (l + "╦") * (s - 1) + l + "╗"
  printf(headerf, *header)
  puts "╠" + (l + "╬") * (s - 1) + l + "╣"

  tab.each do |i|
    printf(rowsf, *i)
  end

  puts "╚" + (l + "╩") * (s - 1) + l + "╝"
end

print_tab(tab(1, $n, $n + $c,
              [method(:fy)]),
          %w[x y(x)])

print_tab(tab(Math::PI / $n, Math::PI, 1.5 * $n + $c,
              [method(:fz)]),
          %w[x z(x)])

print_tab(tab(2, $c, 2 * $n,
              [method(:fy), method(:fz), method(:fun)]),
          %w[x y(x) z(x) y+z])