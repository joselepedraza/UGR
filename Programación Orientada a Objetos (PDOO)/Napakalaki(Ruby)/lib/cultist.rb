# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module NapakalakiGame
class Cultist
  attr_accessor :name
  attr_accessor :gained_levels
  def initialize(nm,glvl)
    @name=nm
    @gained_levels=glvl
  end
end
end