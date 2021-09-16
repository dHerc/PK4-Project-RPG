#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//#include <vld.h>
#include "GameLogic.h"
bool move_right = false, move_left = false,confirm=false,open_menu=false,open_equipement=false,change = false,blocking = false,invisible=false;
int jump = 0, attack = 0, side_attack = 0, down = 0, cooldown = 0, skill = 0;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods );
int main(void)
{
    {
        GLFWwindow* window;
        /* Initialize the library */
        if (!glfwInit())
            return -1;
        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(1920, 1080, "Hello World", glfwGetPrimaryMonitor(), NULL);
        glfwSetKeyCallback(window, keyCallback);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        if (glewInit() != GLEW_OK)
        {
            std::cout << "ERROR!";
            return -1;
        }
        GLCall(glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));
        int lvl_nr=0,state = 0,difficulty=1;
        Renderer renderer;
        float character_offset[2] = { 0.0,-1.0 };
        int turn_right = 1;
        Face face(renderer);
        Skills skills;
        Character archer(character_offset[0], character_offset[1], turn_right, attack, side_attack,skill, renderer,"Archer",200,10,5,40,0);
        Character warrior(character_offset[0], character_offset[1], turn_right, attack, side_attack,skill, renderer, "Warrior",500,10,2,40,1);
        Character mage(character_offset[0], character_offset[1], turn_right, attack, side_attack,skill, renderer, "Mage", 100, 10, 3, 50,2);
        Character assasin(character_offset[0], character_offset[1], turn_right, attack,side_attack,skill, renderer, "Assasin", 150, 10, 10, 5,3);
        Owned inventory;
        Description desc(renderer);
        Equipement equipement(inventory,desc,face,skills, renderer, move_right, move_left, jump, down, confirm);
        Story story(renderer,1);
        bool next_lvl=true;
        while (next_lvl)
        {
            next_lvl = false;
            {
            int world[960][216];
            int char_pos[2] = { 15,4 };
            character_offset[0] = -0.85;
            character_offset[1] = -0.33;
            Background background(character_offset[0], character_offset[1], renderer,lvl_nr);
            Menu menu(renderer, jump, down, confirm);
            Minimenu minimenu(renderer,desc, jump, down, move_right, move_left, confirm, open_menu);
            Overlay overlay(renderer,face);
            GameLogic Game(archer,warrior,mage,assasin,background, menu,minimenu, equipement,story, overlay, renderer, lvl_nr, state, open_menu, open_equipement,difficulty);
            Game.InitializeEnemies(character_offset);
            Game.InitializeDrops(character_offset);
            Game.InitializeNPCs(character_offset);
            /* Loop until the user closes the window */
            while (!glfwWindowShouldClose(window))
            {
                Game.TriggerEQ(true,char_pos);
                if(not invisible)
                    Game.Enemy_Movement(char_pos);
                Game.SetEnemies();
                Game.Movement(move_right, move_left, turn_right, jump, character_offset, char_pos);
                Game.CheckPickups(char_pos);
                Game.Meele(attack, char_pos, turn_right);
                Game.Interact(attack, char_pos, turn_right);
                Game.SideAttack(character_offset,side_attack, char_pos, turn_right,blocking);
                Game.TriggerBoss(character_offset);
                Game.Skill(character_offset, skill, char_pos, turn_right,invisible);
                Game.ResetEnemies();
                Game.Swap(change);
                Game.Regen();
                Game.TriggerEQ(false,char_pos);
                /* Render here */
                int exit = Game.RenderFrame(character_offset);
                if (exit==1)
                {
                    glfwSetWindowShouldClose(window, GL_TRUE);
                    next_lvl = false;
                }
                if (exit == 2)
                {
                    glfwSetWindowShouldClose(window, GL_TRUE);
                    next_lvl = true;
                }
                if (exit == 3)
                {
                    glfwSetWindowShouldClose(window, GL_TRUE);
                    next_lvl = true;
                }
                /* Swap front and back buffers */
                GLCall(glfwSwapBuffers(window));

                /* Poll for and process events */
                GLCall(glfwPollEvents());
            }
            glfwSetWindowShouldClose(window, GL_FALSE);
            }
        }
    }
    glfwTerminate();
    return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        move_right = true;
	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
        move_right = false;
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        move_left = true;
	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
        move_left = false;
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        jump = 1;
	if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
		jump = 0;
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		down = 1;
	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
		down = 0;
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		confirm = 1;
	if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE)
		confirm = 0;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		open_menu = 1;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		open_menu = 0;
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        open_equipement = 1;
    if (key == GLFW_KEY_E && action == GLFW_RELEASE)
        open_equipement = 0;
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        if (attack == 0 && side_attack == 0)
            if(skill==0)
                change = 1;
    if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
        change = 0;
	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        if(attack==0&&side_attack==0)
		    attack = 1;
    if (key == GLFW_KEY_X && action == GLFW_PRESS)
        if (attack == 0 && side_attack == 0)
        {
            side_attack = 1;
            blocking = true;
        }
    if (key == GLFW_KEY_X && action == GLFW_RELEASE)
        blocking = false;
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
        if (skill == 0)
            skill = 1;
}