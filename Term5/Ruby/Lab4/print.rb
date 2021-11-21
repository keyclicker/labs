module Print
  def Print.max_width(a, p)
    maxw = 0
    a.each do |i|
      maxw = [sprintf("%.#{p}f", i).size, maxw].max
    end
    maxw
  end

  # @param [Matrix] m matrix
  # @param [Array] a right part vector
  # @param [Numeric] p precision
  def Print.matrix(m, a = nil, p: 0)
    maxw_m = max_width(m, p)
    format_m = "│" + " %#{maxw_m}.#{p}f" * m.row_size + " │"

    maxw_a = a ? max_width(a, p) : 0
    format_a = a ? "│ %#{maxw_a}.#{p}f │" : ""

    m_array = m.to_a
    m_array.each_index do |i|
      printf(format_m, *m_array[i])
      if a
        print i == m_array.size / 2 ? " = " : "   "
        printf(format_a, a[i])
      end
      puts
    end
  end
end