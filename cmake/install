#!/bin/sh
#

_install () {
	cmd="install $1 $HOME/bin"
	echo $cmd
	$cmd
}

files=$(ls Release/* | grep -v framework | grep guido | grep -v guidoread)
for a in $files
do
	[ -x $a ] && _install $a
done

