using UnityEngine;

[RequireComponent(typeof(SkinnedMeshRenderer))]
public class BlendshapeController : MonoBehaviour
{
    [Header("Serial")]
    [Tooltip("Drag your SerialController here")]
    [SerializeField] private SerialController serialController;

    [Header("Skinned Mesh")]
    [Tooltip("The SkinnedMeshRenderer with your blendshapes")]
    [SerializeField] private SkinnedMeshRenderer skinnedMesh;

    [Header("Blendshape Indices")]
    [Tooltip("Index of the 'eyeLookUpLeft' blendshape")]
    [SerializeField] private int eyeLookUpLeftIndex = 0;
    [Tooltip("Index of the 'eyeLookOutLeft' blendshape")]
    [SerializeField] private int eyeLookOutLeftIndex = 1;
    [Tooltip("Index of the 'jawOpen' blendshape")]
    [SerializeField] private int jawOpenIndex = 2;

    [Header("Smoothing")]
    [Tooltip("Smooth transitions between targets")]
    [SerializeField] private bool smooth = false;
    [SerializeField] private float smoothSpeed = 5f;

    // target weights (0–100)
    private float targetUp, targetOut, targetJaw;

    void Start()
    {
        if (serialController == null)
            serialController = FindObjectOfType<SerialController>();
        if (serialController == null)
        {
            Debug.LogError("SerialController not found!");
            enabled = false;
            return;
        }

        if (skinnedMesh == null)
            skinnedMesh = GetComponent<SkinnedMeshRenderer>();
        if (skinnedMesh == null)
        {
            Debug.LogError("SkinnedMeshRenderer not found!");
            enabled = false;
        }
    }

    void Update()
    {
        string msg = serialController.ReadSerialMessage();
        if (msg == null) return;

        // parse "X,Y|B"
        var p = msg.Split('|');
        if (p.Length != 2) return;
        var xy = p[0].Split(',');
        if (xy.Length != 2) return;

        if (int.TryParse(xy[0], out int x) &&
            int.TryParse(xy[1], out int y) &&
            int.TryParse(p[1], out int b))
        {
            // normalize to –1…1
            float nx = x / 100f;
            float ny = y / 100f;
            // only positive directions mapped
            targetOut = Mathf.Max(0f, nx) * 100f;
            targetUp = Mathf.Max(0f, ny) * 100f;
            targetJaw = (b == 1 ? 100f : 0f);

            ApplyBlendshapes();
        }
    }

    void ApplyBlendshapes()
    {
        if (!smooth)
        {
            skinnedMesh.SetBlendShapeWeight(eyeLookOutLeftIndex, targetOut);
            skinnedMesh.SetBlendShapeWeight(eyeLookUpLeftIndex, targetUp);
            skinnedMesh.SetBlendShapeWeight(jawOpenIndex, targetJaw);
        }
        else
        {
            float curOut = skinnedMesh.GetBlendShapeWeight(
              eyeLookOutLeftIndex
            );
            float curUp = skinnedMesh.GetBlendShapeWeight(
              eyeLookUpLeftIndex
            );
            float curJaw = skinnedMesh.GetBlendShapeWeight(
              jawOpenIndex
            );

            float newOut = Mathf.MoveTowards(
              curOut, targetOut, smoothSpeed * Time.deltaTime
            );
            float newUp = Mathf.MoveTowards(
              curUp, targetUp, smoothSpeed * Time.deltaTime
            );
            float newJaw = Mathf.MoveTowards(
              curJaw, targetJaw, smoothSpeed * Time.deltaTime
            );

            skinnedMesh.SetBlendShapeWeight(eyeLookOutLeftIndex, newOut);
            skinnedMesh.SetBlendShapeWeight(eyeLookUpLeftIndex, newUp);
            skinnedMesh.SetBlendShapeWeight(jawOpenIndex, newJaw);
        }
    }
}
