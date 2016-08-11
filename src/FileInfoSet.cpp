/*
 *   File name: FileInfoSet.cpp
 *   Summary:	Support classes for QZedStat
 *   License:	GPL V2 - See file LICENSE for details.
 *
 *   Author:	Stefan Hundhammer <Stefan.Hundhammer@gmx.de>
 */


#include "FileInfoSet.h"
#include "FileInfo.h"
#include "DirInfo.h"
#include "Logger.h"
#include "Exception.h"


using namespace QZedStat;


bool FileInfoSet::containsAncestorOf( FileInfo * item ) const
{
    while ( item )
    {
	item = item->parent();

	if ( contains( item ) )
	    return true;
    }

    return false;
}


FileInfoSet FileInfoSet::normalized() const
{
    FileInfoSet normalized;

    foreach ( FileInfo * item, *this )
    {
	if ( ! containsAncestorOf( item ) )
	    normalized << item;
#if 0
	else
	    logDebug() << "Removing " << item << " with ancestors in the set" << endl;
#endif
    }

    return normalized;
}


FileInfo * FileInfoSet::first() const
{
    if ( isEmpty() )
	return 0;
    else
	return *begin();
}


bool FileInfoSet::containsDotEntry() const
{
    foreach ( FileInfo * item, *this )
    {
	if ( item  && item->isDotEntry() )
	    return true;
    }

    return false;
}


bool FileInfoSet::containsDir() const
{
    foreach ( FileInfo * item, *this )
    {
	if ( item  && item->isDir() )
	    return true;
    }

    return false;
}


bool FileInfoSet::containsFile() const
{
    foreach ( FileInfo * item, *this )
    {
	if ( item  && item->isFile() )
	    return true;
    }

    return false;
}


bool FileInfoSet::containsSpecial() const
{
    foreach ( FileInfo * item, *this )
    {
	if ( item  && item->isSpecial() )
	    return true;
    }

    return false;
}


bool FileInfoSet::containsBusyItem() const
{
    foreach ( FileInfo * item, *this )
    {
	if ( item  && item->isBusy() )
	    return true;
    }

    return false;
}



FileSize FileInfoSet::totalSize() const
{
    FileSize sum = 0LL;

    foreach ( FileInfo * item, *this )
    {
	if ( item )
	    sum += item->totalSize();
    }

    return sum;
}

