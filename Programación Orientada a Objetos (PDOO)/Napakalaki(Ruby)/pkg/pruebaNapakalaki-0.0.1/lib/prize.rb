#encoding: utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative "bad_consequence.rb"
require_relative "monster.rb"
require_relative "treasure_kind.rb"
module NapakalakiGame
class Prize
  attr_accessor:treasures
  attr_accessor:level
  
  def initialize(trs,lvl)
    @treasures = trs
    @level = lvl
  end
  
  def self.newPrize(trs,lvl)
    new(trs,lvl)
  end

  def to_s
    "Tesoros ganados: #{@treasures}\n Niveles ganados: #{@level}"
  end
end
end