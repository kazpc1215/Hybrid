reset
set view equal xy
set size square
set xr [-2:2]
set yr [-2:2]


#p "./b1000/Planetesimal_posi_rot.dat" u ((($2)-($8))/($13)):((($3)-($9))/($13)) w l,\
#"< tail -1 ./b1000/Planetesimal_posi_rot.dat" u ((($2)-($8))/($13)):((($3)-($9))/($13)):(($7)/($13)) w circle,\
#"< head -2 ./b1000/Planetesimal_posi_rot.dat" u ((($8)-($8))/($13)):((($9)-($9))/($13)):(($13)/($13)) w circle

p "./b1000/Planetesimal_posi_rot.dat" u 2:3 w l,\
"< tail -1 ./b1000/Planetesimal_posi_rot.dat" u 2:3,\
"< head -2 ./b1000/Planetesimal_posi_rot.dat" u 8:9








