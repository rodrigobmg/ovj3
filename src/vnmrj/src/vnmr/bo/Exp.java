/*
 * Copyright (C) 2015  University of Oregon
 *
 * You may distribute under the terms of either the GNU General Public
 * License or the Apache License, as specified in the README file.
 *
 * For more information, see the README file.
 */

package  vnmr.bo;

/**
 * experiment identifier
 *
 * @author Mark Cao
 */
public class Exp extends ID {
    /**
     * constructor
     */

    public Exp(String id) {
	super(id);
    } // Exp()


    public String getName() {
	return id;
    }

    /**
     * indicates whether the given object is equal to this one
     * @return boolean
     */
    public boolean equals(Object obj) {
	if (this == obj)
	    return true;
	if (id != null && obj instanceof Exp)
	    return id.equals(((Exp)obj).id);
	return false;
    } // equals()

} // class Exp
