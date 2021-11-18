def dec_to_bin(dec)
  bin = ""
  while dec > 0
    bin << (dec % 2).to_s
    dec /= 2
  end
  bin.reverse
end

dec = 123

puts "Ruby's to_s(2): #{dec.to_s(2)}"
puts "Custom implementation: #{dec_to_bin(dec)}"