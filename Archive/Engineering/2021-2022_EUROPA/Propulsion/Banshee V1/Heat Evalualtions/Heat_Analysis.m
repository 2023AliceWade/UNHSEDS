clear all; close all;

%% Conductivity from insulator to ambient conditions
% Purpose is to Evaluate different methods of evaluating the heat transfer
% and thermal insulation of our hybrid rocket engine

Tin= 1750; %K Temperature inside the chamber.
Tout= 300 ; %K Ambient Temperature

R1= .07;% Inner Radius of Insulator
R2= .08;% Inner Radius of Chamber Wall
R3= .09;% Outer Radius of Chamber Wall

kI= 3 ;% Coefficient of conduction for Insulator Material
kC= 150 ;  % Coefficient of conduction for Chamber Material W/mK

QdotL=(2*pi*(Tin-Tout))/((log(R2/R1)/kI)+(log(R3/R2)/kC));


%% Conductivity through diminishing fuel grain and insulator

Timelength=linspace(1,10,10);
Length=.31;

R0=linspace(.04,.07,10); %Fuel grain starting inner diameter.
QdotL2sum=0;

for i = 1:length(Timelength)
    QdotL2(i) = (2*pi*(Tin-Tout))/((log(R1/R0(i))/kI)+(log(R2/R1)/kC));
    QdotL2sum=QdotL2sum+QdotL2(i);
end

Qtot=QdotL2sum*Length;

