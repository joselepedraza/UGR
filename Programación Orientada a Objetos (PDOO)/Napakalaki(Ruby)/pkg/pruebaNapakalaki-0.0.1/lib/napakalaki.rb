#encoding: utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative "card_dealer.rb"
require_relative "player.rb"
require_relative "monster.rb"
require_relative "combat_result.rb"
require_relative "bad_consequence.rb"
require_relative "dice.rb"
require_relative "prize.rb"
require_relative "treasure.rb"
require_relative "treasure_kind.rb"

require "singleton"
 
module NapakalakiGame

class Napakalaki

  attr_reader :napakalaki
  attr_accessor :current_player
  attr_accessor :players
  attr_accessor :dealer
  attr_accessor :currentMonster
  
  include Singleton
  
  def initialize
    @currentPlayer
    @players=Array.new
    @dealer= CardDealer.instance
    @currentMonster
  end
  
  def initPlayers(names)
    @players=Array.new
    names.each do|n|
      @players << Player.new(n)  #tb se podría @players.push(n)
    end
  end
=begin
  def nextPlayer
    totalplayers=@players.length #o .size para obtener tamaño
    if @current_player == nil  then#si fuese la primera vez no esta definido el jugador
      nextindice = rand(totalplayers)
      @players[nextindice]
    else
      indicecurrentplayer = @players.index(@current_player)  indice jugador actual 
      @players[(indicecurrentplayer+1)%@players.size]
      end  
    end
=end
  
  def nextPlayer    
    if(@currentPlayer == nil) then
      @indiceCurrentPlayer = rand(@players.size)
    else
      if(@indiceCurrentPlayer == @players.size-1) then
        @indiceCurrentPlayer = 0
      else
        @indiceCurrentPlayer += 1
      end
    end
        
    @currentPlayer = @players.at(@indiceCurrentPlayer)
    @currentPlayer
  end
  
  #Método que comprueba si el jugador activo (currentPlayer) cumple con las reglas del juego
  def nextTurnsIsAllowed
    if @currentPlayer==nil then 
      espermitido=true
    else
      espermitido= @currentPlayer.validState #comprueba en el metodo de Player validState
    end
    espermitido
  end
  
  #Asigna un enemigo a cada jugador de manera aleatoria
  def setEnemies    
    indice=0
    for i in 0..@players.size() - 1
         begin     
            
            indice= rand(@players.size())
            
         end while indice==i
   
          @players[i].setEnemy(@players[indice]) 
        end
  end
  
  def developCombat  
    #puts 'MONSTER', @currentMonster
    combate = @currentPlayer.combat(@currentMonster)
    @dealer.giveMonsterBack(@currentMonster)
    if(combate == CombatResult::LOSEANDCONVERT) then
      c= @dealer.nextCultist
      c1 = CultistPlayer.new(@currentPlayer, c)
      
      @players.each do |p|
        if p.getEnemy == @currentPlayer then
          p.setEnemy(c1)
        end
      end
      @players.delete(@currentPlayer)
      @players << c1 
    end
    combate
  end 
  
  def discardVisibleTreasures(treasures)
    treasures.each do |t|
      @currentPlayer.discardVisibleTreasure(t)
      @dealer.giveTreasureBack(t)
    end
  end
  def discardHiddenTreasures(treasures)
    treasures.each do |t|
      @currentPlayer.discardHiddenTreasure(t)
      @dealer.giveTreasureBack(t)
    end
  end
  def makeTreasuresVisible(treasures)
    treasures.each do |t|
      @currentPlayer.makeTreasureVisible(t)   #tengo mis dudillas aqui xD
    end
  end  
  
  def initGame(players)
    initPlayers(players)
    setEnemies
    
    @dealer.initCards
    
    nextTurn
  end
  
  def getCurrentPlayer
    @currentPlayer
  end
  def getCurrentMonster
    @currentMonster
  end
  
  def nextTurn 
    stateok = nextTurnsIsAllowed
    puts 'State', stateok
    if stateok then
      @currentMonster = @dealer.nextMonster
      @currentPlayer = nextPlayer()
      dead = @currentPlayer.isDead
      if dead then
        @currentPlayer.initTreasures
      end
    end
    
    stateok
  end
  
  def endOfGame(result)
    endgame=false
    if result == WINGAME
      endgame=true
    end
   endgame
  end
end
end