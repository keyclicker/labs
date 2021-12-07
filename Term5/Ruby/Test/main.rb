class Field
  attr_accessor :value
  def initialize(value)
    @value = value
  end
end

class Phone < Field
end

class Skype < Field
end

class Email < Field
end

class Social < Field
end

class Contact
  attr_accessor :name, :phone, :skype, :email, :social
  def initialize(name = nil, phone = nil, skype = nil, email = nil, social = nil)
    @name = name
    @phone = Phone.new(phone)
    @skype = Skype.new(skype)
    @email = Email.new(email)
    @social = Social.new(social)
  end

  def merge(c)
    Contact.new(name || c.name, phone.value || c.phone.value,
                skype.value || c.skype.value, email.value || c.email.value,
                social.value || c.social.value)
  end

  def to_s
    "#{name.to_s}: { #{phone.value}, #{skype.value}, #{email.value}, #{social.value} }"
  end
end

class Contacts
  def initialize
    @contacts = []
  end

  def add(contact)
    @contacts.push(contact)
  end

  def to_s
    res = ''
    @contacts.each do |a|
      res += "#{a}\n"
    end
    res
  end

  def sort_by_phone
    @contacts.sort_by(&:phone.value)
  end

  def sort_by_name
    @contacts.sort_by(&:name)
  end

  def find_by_name(name)
    @contacts.select { |c| c.name.include? name}
  end

  def find_by_phone(phone)
    @contacts.select { |c| c.phone.value.include? phone}
  end
end

def a_to_s(arr)
  res = ''
  arr.each do |a|
    res += "#{a}\n"
  end
  res
end

con1 = Contact.new("Jack Nicholson","88805553535", "@skype", nil, "@sjkl")
con2 = Contact.new("Brad Pitt", "80080880808", nil, "br@pi.tt", "@dsfdsfdsf")

contacts = Contacts.new
contacts.add(con1)
contacts.add(con2)
contacts.add(con1.merge(con2))

puts "#{contacts}\n\n"
puts "#{a_to_s(contacts.sort_by_name)}\n\n"
puts "#{a_to_s(contacts.find_by_name("Ni"))}\n\n"
puts "#{a_to_s(contacts.find_by_phone("008"))}\n\n"