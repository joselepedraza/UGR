/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalaki;
import GUI.Dice;
import GUI.NapakalakiView;
import java.util.*;
import GUI.PlayerNamesCapture;
        
/**
 *
 * @author joseperoman
 */
public class Principal {
    public static void main (String[] args){
        Napakalaki game = Napakalaki.getInstance();
        NapakalakiView napakalakiView = new NapakalakiView();
        
        Dice.createInstance (napakalakiView);

        //napakalakiView.setNapakalaki(game);

        //napakalakiView.setVisible(true);

        ArrayList<String> names;
        PlayerNamesCapture namesCapture = new PlayerNamesCapture(napakalakiView, true);
        
        names = namesCapture.getNames();
        game.initGame(names);
        
        napakalakiView.setNapakalaki(game);
        napakalakiView.setVisible(true);
        napakalakiView.showView();
    }
}


