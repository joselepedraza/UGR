#encoding: utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative "bad_consequence.rb"
require_relative "prize.rb"
require_relative "treasure_kind.rb"
module NapakalakiGame
class Monster
  attr_accessor:name
  attr_accessor:combatLevel
  attr_accessor:prize
  attr_accessor:badConsequence
  attr_accessor:level_change_against_cultist_player
  
  def initialize(nm,cbLvl,pr,bc)
    @name=nm
    @combatLevel=cbLvl
    @prize=pr
    @badConsequence=bc
    @level_change_against_cultist_player=0
  end
=begin
  def self.newMonster(nm,clvl,bc,pr)
    new(nm,clvl,bc,pr)
  end
=end
  def Monster.newMonster(n,l,p,bc,lc)
    @name=n
    @combatLevel=l
    @prize=p
    @badConsequence=bc
    @level_change_against_cultist_player=lc
  end
  def getCombatLevel
    @combatLevel
  end
  def getLevelsGained
    @prize.level
  end
  
  def getTreasuresGained
    @prize.treasures
  end
  
  def getCombatLevelAgainstCultistPlayer
    @combatLevel + @level_change_against_cultist_player
  end
  
  def to_s
    "Nombre: #{@name}\n Nivel de combate: #{@combatLevel}\n Buen rollo:#{@prize}\n Mal rollo: #{@badConsequence}"
  end
  
end
end