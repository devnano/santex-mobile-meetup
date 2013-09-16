#pragma strict

//The scene's default fog settings
private var defaultFog;
private var defaultFogColor;
private var defaultFogDensity;
private var defaultSkybox;
var noSkybox : Material;

function Start () {

}

function Update () {
		RenderSettings.fog = true;
		RenderSettings.fogColor = Color (0, 0.4, 0.7, 0.6);
		RenderSettings.fogDensity = 0.04;
		RenderSettings.skybox = noSkybox;
}