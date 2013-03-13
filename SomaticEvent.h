#ifndef SOMATIC_EVENT_H
#define SOMATIC_EVENT_H

/**
 * @file SomaticEvent.h
 * Interface description of data structure class SomaticEvent
 * 
 * @author Yi Qiao
 */

#include "Archivable.h"
#include <vector>

namespace SubcloneExplorer {

	/**
	 * @brief Abstract data structure class that represents any type of somatic mutation
	 *
	 * The most important aspect of the mutations represented by this class
	 * is that it has an cell frequency associated, which describes in what
	 * fraction of the cells does this specific event exist
	 */
	class SomaticEvent : public Archivable {
		protected:
			// Implements Archivable
			virtual std::string createTableStatementStr();

			sqlite3_int64 ofClusterID; /**< to which cluster in database does this event belongs */

		public:
			double frequency; /**< Cell frequency */

			/**
			 * minimal constructor to reset member variables
			 */
			SomaticEvent(): Archivable(), ofClusterID(0), frequency(0) {;}

			/**
			 * Set the cluster's database id to which this event belongs
			 *
			 * @param clusterID The cluster's database record id
			 */
			inline void setClusterID(sqlite3_int64 clusterID) {ofClusterID = clusterID;}

			/**
			 * Check equality
			 *
			 * @param anotherEvent The other SomaticEvent object to compare to
			 * @param resolution The boundry resolution with respect to chromosome location
			 *
			 * @return whether two SomaticEvent objects are representing the same event
			 */

			virtual bool isEqualTo(SomaticEvent * anotherEvent, unsigned long resolution=10000L) {return false;}
			/**	 
			 * Retrieve cluster id this event belongs to
			 *
			 * @return the cluster id
			 */
			inline sqlite3_int64 clusterID() {return ofClusterID;}

			/**
			 * Return all objects with the given cluster id as their parent
			 *
			 * @returm a vector of objectIDs (whose type depends on concrete class)
			 */
			virtual DBObjectID_vec allObjectsOfCluster(sqlite3 *database, sqlite3_int64 clusterID);

	};

	/**
	 * A vector of SomaticEvent Pointers
	 */
	typedef std::vector<SomaticEvent *> SomaticEventPtr_vec;
}

#endif
