# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative "bad_consequence.rb"
require_relative "numeric_bad_consequence.rb"
module NapakalakiGame
class DeathBadConsequence < NumericBadConsequence
  attr_accessor :death
  def initialize(txt)
    super(txt,0,0,0)
    @death=true
  end
  
  def to_s
    "#{@text}\n Niveles perdidos: #{@levels}\n Muerto: #{@death}" 
  end
  
end

end