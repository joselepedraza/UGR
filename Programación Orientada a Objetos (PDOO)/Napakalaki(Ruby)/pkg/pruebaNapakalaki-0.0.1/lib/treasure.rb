# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module NapakalakiGame
class Treasure
  attr_accessor :name
  attr_accessor :bonus
  attr_reader :type
  
  def initialize(nm,bns,t)
    @name=nm
    @bonus=bns
    @type=t
  end
  def getType
    @type
  end
  def to_s
    return " Nombre:[#{@name}]  Bonus:#{@bonus}  Tipo:#{@type}"
  end
end
end