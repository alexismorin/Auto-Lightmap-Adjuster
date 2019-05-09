using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class AdjustLightmaps : MonoBehaviour {
    [MenuItem ("Tools/Adjust Lightmap Scale - Mobile")]
    static void generateLow () {
        generateLightmapScale (15f);
    }

    [MenuItem ("Tools/Adjust Lightmap Scale - Desktop and Consoles")]
    static void generateMedium () {
        generateLightmapScale (10f);
    }

    [MenuItem ("Tools/Adjust Lightmap Scale - Film and TV Rendering")]
    static void generateHigh () {
        generateLightmapScale (5f);
    }

    static void generateLightmapScale (float ratio) {
        GameObject[] objectsInScene = UnityEngine.Object.FindObjectsOfType<GameObject> ();
        foreach (GameObject obj in objectsInScene) {
            if (obj.isStatic) {

                if (obj.GetComponent<Renderer> () != null) {
                    Vector3 objectVolume = obj.GetComponent<Renderer> ().bounds.size;
                    print (Mathf.Clamp (objectVolume.magnitude, 2.5f, 10f));
                    SerializedObject so = new SerializedObject (obj.GetComponent<Renderer> ());
                    so.FindProperty ("m_ScaleInLightmap").floatValue = Mathf.Clamp (objectVolume.magnitude, 2.5f, 10f) / ratio;
                    //   print ();
                    so.ApplyModifiedProperties ();
                }

            }
        }
    }
}