# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative "player.rb"
module NapakalakiGame
class CultistPlayer < Player
  attr_accessor :my_cultist_card
  @@total_cultits_players=0
  
  
  def initialize(p,c)
    #copiarJugador(p)
    super(p.name)
    @my_cultist_card=c
    @@total_cultits_players+=1
  end
  
  def getCombatLevel
    nivel= super
    lvl= (nivel+(1/5*nivel))+ @my_cultist_card.ganied_levels*@@total_cultist_players
    lvl = lvl.round
    lvl
  end
  
  def getOponentLevel(m)
    return m.getCombatLevelAgainstCultistPlayer
  end
  
  def shouldConvert
    return false
  end
  
  def giveMeATreasure
    rnd = rand(@visibleTreasures.size)
    return @visibleTreasures.get(rand)
  end
  
  def canYouGiveMeATreasure
    tama = @visibleTreasures.size
    if tama > 0 then
      return true
    else
      return false
    end
  end
  
  def self.getTotalCultistPlayers
    return @@total_cultist_players
  end
end
end