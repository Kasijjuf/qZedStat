/*
 *   File name: Refresher.h
 *   Summary:	Helper class to refresh a number of subtrees
 *   License:	GPL V2 - See file LICENSE for details.
 *
 *   Author:	Stefan Hundhammer <Stefan.Hundhammer@gmx.de>
 */


#include "Refresher.h"
#include "DirTree.h"
#include "FileInfoSet.h"
#include "Logger.h"

using namespace QZedStat;


Refresher::Refresher( const FileInfoSet items, QObject * parent ):
    QObject( parent ),
    _items( items )
{
    // logDebug() << "Creating refresher for " <<  _items.size() << " items" << endl;
}


void Refresher::refresh()
{
    if ( ! _items.isEmpty() )
    {
	// Don't try to log any item URL etc.: The item might have become
	// invalid in the meantime.
	logDebug() << "Refreshing " << _items.size() << " items" << endl;

	DirTree * tree = _items.first()->tree();
	tree->refresh( _items );
    }
    else
    {
	logWarning() << "No items to refresh" << endl;
    }

    this->deleteLater();
}


FileInfoSet Refresher::parents( const FileInfoSet children )
{
    FileInfoSet parents;

    foreach ( FileInfo * child, children )
    {
	if ( child && child->parent() )
        {
            FileInfo * parent = child->parent();

            if ( parent->isDotEntry() )
                parent = parent->parent();

            if ( parent )
                parents << parent;
        }
    }

    return parents.normalized();
}

