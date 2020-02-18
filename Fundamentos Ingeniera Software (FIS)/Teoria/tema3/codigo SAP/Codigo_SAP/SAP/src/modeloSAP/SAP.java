/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package modeloSAP;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 *
 * @author aanaya
 */
public class SAP {
    
    private PlanEstudios pe;
    private List<Proyecto> proyectos = new ArrayList ();
    private List<Profesor> profesores = new ArrayList ();
  
    public void definirProyecto(String dni, String titulo, int numAlum,String descripcion,List<String> listaCodAsig)
                        throws Exception
    {
        if(numAlum<1 || numAlum>3) throw new Exception ("número de alumnos debe estar entre 1 y 3");
        Profesor prof = buscarProfesor(dni);
        List<Asignatura> asigs = pe.obtenerAsignaturas(listaCodAsig);
        Proyecto pro = new Proyecto (titulo, numAlum, descripcion,prof, asigs);      
        proyectos.add(pro);
        prof.incluirProyecto(pro);        
    }
    
    private Profesor buscarProfesor(String dni) throws SAPException {
        Profesor prof=null;
        boolean encontrado = false;
        for (Iterator<Profesor> it = profesores.iterator(); (it.hasNext()&!encontrado);) {
           prof = it.next();
            if(prof.getDni().equals(dni))
                encontrado = true;           
        }
        if(!encontrado) throw new SAPException("profesor no encontrado");
        return prof;
       
    }
}
