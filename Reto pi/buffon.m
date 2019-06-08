%inicializar Ncorta y n
Ncorta=0; %número de veces que la aguja corta o toca la l?nea 
n=0; %numero de lanzamientos 
%inicializar l, d, y Ntotal
Ntotal=3000; %numero total de lanzamientos de la aguja
l=10; %longitud de la aguja
d=20; %espaciado entre lineas paralelas donde d>=l
while(n<Ntotal)
%generar dos numeros pseudoaletorios u1, u2
u1 = random('Uniform',0,1);
u2 = random('Uniform',0,1);
%calcular a y angulo
a=(d/2)*(u1);
angulo=180*u2;
%procedimiento para saber si la aguja toca la linea
if a <= ((l/2)*(sind(angulo)))
n=n+1;
Ncorta=Ncorta+1;
else
n=n+1;
end
end
p=Ncorta/Ntotal;
pi=(2*l)/(p*d);
disp(pi);