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
 * RecordData identifier
 *
 */
public class RecordData extends ID {
    /**
     * constructor
     */
    public RecordData(String id) {
	super(id);
    } // RecordData()

    /**
     * Get RecordData name. For now, just use the id for the name.
     * @return name
     */
    public String getName() {
	return id;
    } // getName()

    /**
     * indicates whether the given object is equal to this one
     * @return boolean
     */
    public boolean equals(Object obj) {
	if (this == obj)
	    return true;
	if (id != null && obj instanceof RecordData)
	    return id.equals(((RecordData)obj).id);
	return false;
    } // equals()

} // class RecordData
