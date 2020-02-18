# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require "singleton"

module NapakalakiGame
class Dice
  #attr_accessor:dice
  include Singleton
  def initialize
    #@dice
  end
  
  def nextNumber
    1 + rand(6)  #Genera número aleatorio entre 1 y 6(ambos incluidos)
  end
=begin
  def self.getInstance
    Dice.instance
  end
=end
end
end