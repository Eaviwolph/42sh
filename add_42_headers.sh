#!/bin/zsh

makefile_header="# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: 42shTeam <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/03 15:35:21 by 42shTeam          #+#    #+#              #
#    Updated: 2017/05/03 15:35:21 by 42shTeam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #\n"       

c_header="/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42shTeam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:35:21 by 42shTeam          #+#    #+#             */
/*   Updated: 2017/05/03 15:35:21 by 42shTeam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */\n" 

add_42_headers() {
    cd srcs
    for file in $(find . -name "*.c"); do
      add_42_header "$file"
      echo -n "."
    done
    cd ../includes
    for file in $(find . -name "*.h"); do
      add_42_header "$file"
      echo -n "."
    done
    cd ..
    add_42_header "Makefile"
    echo "."
    
    # git status
    # git diff
    # git add srcs includes Makefile
    # git commit -m "[mod] add 42 headers on top of files."
}

add_42_header() {
    src_file=$1
    tmp="/tmp/42_header"
	first_chars=$(head -c 3 $src_file)
	if [ $first_chars = "/* " ]; then
		return
	fi
    if [ $src_file = "Makefile" ]; then
        echo $makefile_header > $tmp
    else
        echo $c_header > $tmp
    fi
    cat $src_file >> $tmp
    cp $tmp $src_file
}

add_42_headers
