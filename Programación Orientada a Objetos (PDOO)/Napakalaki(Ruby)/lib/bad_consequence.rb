#encoding: utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative "prize.rb"
require_relative "monster.rb"
require_relative "treasure_kind.rb"

module NapakalakiGame
class BadConsequence

  @@MAXTREASURES=10
  attr_accessor:text
  attr_accessor:levels
  attr_accessor:nVisibleTreasures
  attr_accessor:nHiddenTreasures
  attr_accessor:death
  attr_accessor:specificVisibleTreasures
  attr_accessor:specificHiddenTreasures
  
  
  def initialize(aText,someLevels)
    @text=aText  #txt
    @levels=someLevels  #lvls
  end
 
  def isEmpty()
  end
   
  def substractVisibleTreasures(t)
  end
 
  def substractHiddenTreasures(t)
  end
 
  def setnVisibleTreasures(nV)
  end
  
  def setnHiddenTreasures(nH)
  end
  
  def adjustToFitTreasureList(v,h)
  end

  def to_s
    "#{@text}\n Niveles perdidos: #{@levels}" 
  end
  
end
end