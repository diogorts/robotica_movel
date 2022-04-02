#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "kbhit.h"

#define VERMELHO "\x1b[31m"
#define VERDE "\033[1;92m"
#define AMARELO "\033[1;33m"

#define RESET "\033[0;0m"

int main(int argc, char **argv){

    ros::init(argc, argv, "Atividade_1");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
    ros::Rate loop_rate(10);
    geometry_msgs::Twist msg;
    system("rosservice call reset");

    char letra;
    int reset = 1;
    float velLin = 0;
    int velAng = 0;
    int bateria = 100;

    float count = 0;
    while (ros::ok())
    {
        if(kbhit()){
            letra = getchar();

            // Acao para cada letra
            if(letra != 'p'){

                switch (letra){
                    case 'w': velLin=1;velAng=0; printf(VERDE"[Movimentando: Pra Frente]\n"RESET); break;
                    case 'x': velLin=-1;velAng=0; printf(VERDE"[Movimentando: Pra Tras]\n"RESET); break;
                    case 'a': velLin=0;velAng=M_PI/2; printf(VERDE"[Movimentando: Girando para Esquerda]\n"RESET); break;
                    case 'd': velLin=0;velAng=-M_PI/2; printf(VERDE"[Movimentando: Girando para Direita]\n"RESET); break;

                    case 's': velLin=0; velAng=0; printf(AMARELO"[Parado: Aguardando comando]\n"RESET); break;

                    case 'q': velLin=1;velAng = M_PI/2; printf(VERDE"[Movimentando: Curva pra Esquerda/Frente]\n"RESET); break;
                    case 'z': velLin=-1;velAng = -M_PI/2; printf(VERDE"[Movimentando: Curva pra Esquerda/Tras]\n"RESET); break;
                    case 'e': velLin=1;velAng = -M_PI/2; printf(VERDE"[Movimentando: Curva pra Direita/Frente]\n"RESET); break;
                    case 'c': velLin=-1;velAng = M_PI/2; printf(VERDE"[Movimentando: Curva pra Direita/Tras]\n"RESET); break;

                    case '1': velLin+=1; printf(AMARELO"[Acao: Aumentando velocidade linear]\n"RESET); break;
                    case '2': velLin-=1; printf(AMARELO"[Acao: Diminuindo velocidade linear]\n"RESET); break;
                    case '3': velAng+=1; printf(AMARELO"[Acao: Aumentando velocidade angular]\n"RESET); break;
                    case '4': velAng-=1; printf(AMARELO"[Acao: Diminuindo velocidade angular]\n"RESET); break;

                    case 'r':  break;

                    default:
                        printf(AMARELO"\nTecla invalida! Por favor, tente novamente..."RESET);
                        break;
                }
            }else{
                printf(VERMELHO"Programa finalizado.\n\n"RESET);
                return 0;
            }
        }
        msg.linear.x = velLin;
        msg.angular.z = velAng;
        pub.publish(msg);
        //ros::spinOnce();
        
        pub.publish(msg);
        
        ros::spinOnce();
        
        loop_rate.sleep();
        
        
    }
    
    return 0;

} // fim main