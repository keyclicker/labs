def bin_to_dec(bin)
  dec = 0
  bin.reverse.split('').each_with_index { |c, i|
    dec += c.to_i * 2 ** i;
  }
  dec
end

bin = "1000010001"

puts "Ruby's to_i(2): #{bin.to_i(2)}"
puts "Custom implementation: #{bin_to_dec(bin)}"