#include "OGameInstance.h"

int main() {
	OGameInstance OGame;

	//VulkanRenderer renderer;
	//
	//try {
	//	renderer.init();
	//}
	//catch (const std::runtime_error& e) {
	//	std::cerr << e.what() << std::endl;
	//	return EXIT_FAILURE;
	//}
	////PHYSICS =============================================================
	//b2Vec2 gravity(glm::vec2(-0.5f, -0.01f));
	//b2World world(gravity);

	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(0.0f, -10.0f);
	//b2Body* groundBody = world.CreateBody(&groundBodyDef);
	//b2PolygonShape groundBox;
	//groundBox.SetAsBox(10.0f, 5.0f);
	//groundBody->CreateFixture(&groundBox, 0.0f);

	//// Define the dynamic body. We set its position and call the body factory.
	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0.0f, 10.0f);
	//bodyDef.allowSleep = false;
	////bodyDef.gravityScale = 0.f;
	//bodyDef.linearDamping = 0.f;
	//b2Body* body = world.CreateBody(&bodyDef);
	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(0.2f, 0.2);
	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &dynamicBox;
	//fixtureDef.density = 100.0f;
	//fixtureDef.friction = 0.3f;
	//fixtureDef.restitution = 0.2f;
	//body->CreateFixture(&fixtureDef);

	//// Prepare for simulation. Typically we use a time step of 1/60 of a
	//// second (60Hz) and 10 iterations. This provides a high quality simulation
	//// in most game scenarios.
	//float32 timeStep = 1.0f / 60.0f;
	//int32 velocityIterations = 6;
	//int32 positionIterations = 2;
	//
	////STATIC MESH ================================================================
	//PlaneMesh testPlane(glm::vec2(10.f, 5.f), &renderer);
	//PlaneMesh testPlane2(glm::vec2(0.2f, 0.2f), &renderer);
	//
	//PhysicalObject testObject;
	//testObject.createRenderTask(&renderer);
	//testObject.getTask()->setMesh(&testPlane);
	//testObject.setPosition(&glm::vec3(groundBody->GetPosition().x, groundBody->GetPosition().y, 0.f));
	//
	//PhysicalObject testObject2;
	//testObject2.createRenderTask(&renderer);
	//testObject2.getTask()->setMesh(&testPlane2);
	//testObject2.setPosition(&glm::vec3(body->GetPosition().x, body->GetPosition().y, -0.f));
	//
	//std::vector<PhysicalObject*> objects;
	//objects.push_back(&testObject);
	//objects.push_back(&testObject2);

	////std::vector<PhysicalObject*> dynamicObjects;
	//for (int i = 0; i < 11; i++){
	//	for (int j = 0; j < 5; j++){
	//		objects.push_back(new PhysicalObject);
	//		objects.back()->createRenderTask(&renderer);
	//		objects.back()->getTask()->setMesh(&testPlane2);
	//		objects.back()->setPosition(&glm::vec3((i - 11.f/2.f), (j -  5.f/2.f), -0.f));
	//		objects.back()->createCollider(&bodyDef, &fixtureDef, &world);
	//	}
	//}

	//Player player_one(renderer.getWindow());
	//SpaceshipFighter space_fighter;
	//player_one.getController()->Possess(&space_fighter);
	//space_fighter.createRenderTask(&renderer);
	//space_fighter.getTask()->setMesh(&testPlane2);
	//space_fighter.createCollider(&bodyDef, &fixtureDef, &world);
	//space_fighter.setPosition(glm::vec3(0.f, 0.f, -0.f));
	//

	////SCENEGRAPH =================================================================

	//std::vector<VkRenderTask*> render_tasks;
	//
	//for ( auto & object : objects)
	//	render_tasks.push_back(object->getTask());

	//render_tasks.push_back(space_fighter.getTask());

	//renderer.recordCommandBuffer(render_tasks);

	//

	////RENDERLOOP ===================================================================
	//GameState game_state;
	//while (!glfwWindowShouldClose(renderer.getWindow())) {
	//	glfwPollEvents();
	//	game_state.Tick();

	//	if (game_state.getTotalTime() > 3.0)
	//		world.SetGravity(b2Vec2(glm::vec2(0.5f, -0.01f)));

	//	world.Step(game_state.getDeltaTime(), velocityIterations, positionIterations);

	//	for (const auto & object : objects)
	//		object->Tick();
	//	
	//	space_fighter.update();

	//	renderer.updateCamera(&game_state);
	//	renderer.updateUniformBuffer();
	//	renderer.drawFrame();
	//}

	//testObject.destroyRenderTask();
	//testObject2.destroyRenderTask();
	//for (int i = 2; i < objects.size(); i++)
	//{
	//	delete objects[i];
	//}

	//return EXIT_SUCCESS;
}