
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

struct vector_s {
    float x, y, z = 0;
};

struct result_s {
    float results[6] = { 0 };
    char axis = '\0';
};
const char result_axis[6] = { 'x', 'y', 'z', 'X', 'Y', 'Z' };

const float weights[][12] = {
    {-1.0817570686340332,-1.655733585357666,2.1388723850250244,-1.0508112907409668,-1.4393140077590942,-0.952399730682373,0,0,0,0,0,0},
    {0.46537384390830994,0.01998959295451641,0.7300423979759216,1.1989277601242065,0.6826568245887756,1.68205988407135,0,0,0,0,0,0},
    {1.9955260753631592,1.4054962396621704,-0.8963221311569214,-0.71615070104599,0.6558716297149658,-0.7395864129066467,0,0,0,0,0,0},
    {0.035530585795640945,0.035530585795640945,0.035530585795640945,0.035530585795640945,0.035530585795640945,0.035530585795640945,0,0,0,0,0,0},

    {1.1925675868988037,1.22749662399292,-0.4483449161052704,1.6203052997589111,1.454071044921875,0.043179333209991455,-0.4433841109275818,0.509141743183136,0.9890922904014587,0.6747674345970154,-0.44661879539489746,-1.2123438119888306},
    {1.4574897289276123,0.3406597673892975,-0.07728856801986694,1.1930192708969116,2.2732138633728027,0.08753082156181335,-0.3810584843158722,1.1602634191513062,0.6093558669090271,-1.435186743736267,-0.004888415336608887,-1.7143181562423706},
    {-1.309162974357605,1.0337063074111938,-0.09200532734394073,-0.877862811088562,-0.6439349055290222,-0.049762263894081116,-0.05306670442223549,-1.7899222373962402,-0.3105882406234741,1.0277615785598755,-0.287304550409317,1.9534080028533936},
    {1.396445393562317,-1.9765183925628662,0.08484584838151932,0.8854844570159912,-0.7899835109710693,1.4632527828216553,0.057419657707214355,1.4858943223953247,1.1603325605392456,-1.4791359901428223,-0.030815541744232178,1.6680502891540527},
    {0.7140852808952332,-0.9652336835861206,0.19757260382175446,1.4596248865127563,1.6914433240890503,1.202843189239502,0.08049988001585007,1.3033722639083862,1.3836138248443604,-1.7629765272140503,-0.49427828192710876,-0.8818818926811218},
    {0.7929177284240723,-1.5664275884628296,0.1457226723432541,0.544022798538208,-1.072762131690979,1.6344534158706665,0.26667532324790955,0.45674434304237366,1.0276355743408203,-1.6445635557174683,-0.4014139175415039,1.3691474199295044},
    {0.2761710584163666,0.2761710584163666,0.2761710584163666,0.2761710584163666,0.2761710584163666,0.2761710584163666,0.2761710584163666,0.2761710584163666,0.2761710584163666,0.2761710584163666,0.2761710584163666,0.2761710584163666},

    {1.2376689910888672,-1.487162470817566,-1.7837719917297363,-1.0383323431015015,-0.013784082606434822,0.21855203807353973,0,0,0,0,0,0},
    {-2.296278953552246,0.6308854818344116,-1.6804684400558472,0.7070935368537903,-1.7493088245391846,0.20425735414028168,0,0,0,0,0,0},
    {-0.1472562849521637,0.11731348931789398,-0.1946079134941101,-0.24264952540397644,-0.016291391104459763,-0.5082353353500366,0,0,0,0,0,0},
    {0.06976774334907532,-0.903166651725769,-2.143077850341797,-1.3912733793258667,0.08119159936904907,0.28325119614601135,0,0,0,0,0,0},
    {0.4753589928150177,1.0419690608978271,-1.7908614873886108,-2.6107239723205566,-0.5350163578987122,1.1030380725860596,0,0,0,0,0,0},
    {0.7209710478782654,-0.8891912698745728,0.1968960464000702,-1.3448193073272705,1.0284152030944824,-0.8495633006095886,0,0,0,0,0,0},
    {0.006484864745289087,0.027908841148018837,-0.16552744805812836,-0.06935454905033112,0.5590983033180237,-0.1525299996137619,0,0,0,0,0,0},
    {1.7014656066894531,-0.5474828481674194,-0.5181624889373779,-0.3895600438117981,-1.045999526977539,-0.7666702270507812,0,0,0,0,0,0},
    {0.26823803782463074,-0.5634336471557617,0.14765594899654388,-1.5356829166412354,0.8061796426773071,0.6544430255889893,0,0,0,0,0,0},
    {-0.43428218364715576,-0.014732491225004196,-1.679282546043396,1.5443116426467896,-0.915833592414856,-1.9731526374816895,0,0,0,0,0,0},
    {-0.09125080704689026,-0.3563230335712433,-0.22241681814193726,0.3998664617538452,-0.5593847632408142,0.2731550931930542,0,0,0,0,0,0},
    {-1.837878942489624,-0.23473016917705536,1.5119633674621582,0.41594213247299194,-0.010581817477941513,-2.4069864749908447,0,0,0,0,0,0},
    {-0.5146099328994751,-0.5146099328994751,-0.5146099328994751,-0.5146099328994751,-0.5146099328994751,-0.5146099328994751,0,0,0,0,0,0}
};

//  Function prototypes
void nnevaluate(vector_s input, result_s* output);
float nnactivationfunction(float input);
void decoderesults(result_s* inputresults);

//  Main program
int main() {
    vector_s testpoint;
    result_s nnresults;

    // Get values to be evaluated from user
    cout << "Enter X value: ";
    cin >> testpoint.x;
    cout << "Enter Y value: ";
    cin >> testpoint.y;
    cout << "Enter Z value: ";
    cin >> testpoint.z;
    cout << "\nTest axis values (XYZ): " << testpoint.x << ' ' << testpoint.y << ' ' << testpoint.z << "\n\n";

    nnevaluate(testpoint, &nnresults);
    decoderesults(&nnresults);
    cout << "Evaluation: ";
    switch (nnresults.axis) {
    case 'x':
        cout << "Negative X";
        break;

    case 'y':
        cout << "Negative Y";
        break;

    case 'z':
        cout << "Negative Z";
        break;

    case 'X':
        cout << "Positive X";
        break;

    case 'Y':
        cout << "Positive Y";
        break;

    case 'Z':
        cout << "Positive Z";
        break;

    default:
        cout << "ERR";
        break;
    }
    cout << " is pointed up with a confidence of "
        << *max_element(nnresults.results, nnresults.results + 6) * 100 << "%\n\n";

    return 0;
}

//  Functions

void nnevaluate(const vector_s input, result_s* output) {
    //  Layer array inits
    float input_l[3] = { (float)(input.x / 4096), (float)(input.y / 4096), (float)(input.z / 4096) };
    float hidden1_l[6] = { 0 };
    float hidden2_l[12] = { 0 };
    float output_l[6] = { 0 };

    float* conlayers[] = { input_l, hidden1_l, hidden2_l, output_l };
    const int conlayersizes[] = {
        sizeof(input_l) / sizeof(input_l[0]),
        sizeof(hidden1_l) / sizeof(hidden1_l[0]),
        sizeof(hidden2_l) / sizeof(hidden2_l[0]),
        sizeof(output_l) / sizeof(output_l[0])
    };
    const int conlayercount = sizeof(conlayers) / sizeof(conlayers[0]);

    int weightindexoffset = 0;

    for (int conlayer = 0; conlayer < (conlayercount - 1); conlayer++) {

        const float* sourcelayer = conlayers[conlayer];
        float* destlayer = conlayers[conlayer + 1];

        const int inputlength = conlayersizes[conlayer] + 1; // Add 1 input node for bias
        const int outputlength = conlayersizes[conlayer + 1];

        for (int idxout = 0; idxout < outputlength; idxout++) {
            for (int idxin = 0; idxin < inputlength; idxin++) {
                const float weight = weights[idxin + weightindexoffset][idxout];
                float inval;
                if (idxin == (inputlength - 1)) {
                    inval = 1.0;
                }
                else {
                    inval = sourcelayer[idxin];
                }
                destlayer[idxout] += inval * weight;
                cout << "Input node: " << idxin << "\tOutput node: " << idxout << "\tInVal: " << inval << "\tWeight: " << weight << " @ " << (idxin + weightindexoffset) << " " << (idxout) << "\tResult: " << (inval * weight) << "\n";
            } // Input node loop

            destlayer[idxout] = nnactivationfunction(destlayer[idxout]);
            cout << "Result: " << destlayer[idxout] << "\n\n";
        } // Output node loop
        cout << "\n";
        weightindexoffset += inputlength;
    } // Layer connecting web layer loop

    for (int i = 0; i < (sizeof(output_l) / sizeof(output_l[0])); i++) {
        output->results[i] = output_l[i];
    }
}

//#define NN_ALG_BINSTEP
//#define NN_ALG_LINEAR
//#define NN_ALG_SIGMOID
#define NN_ALG_TANH

#define BINSTEP_TRESHOLD 0.5

float nnactivationfunction(float input) {
#ifdef NN_ALG_BINSTEP

    if (input >= BINSTEP_TRESHOLD) {
        return 1.0;
    }
    else {
        return 0.0;
    }

#elif defined NN_ALG_LINEAR

    return input;

#elif defined NN_ALG_SIGMOID

    return (1 / (1 + exp(-input)));

#elif defined NN_ALG_TANH

    return ((exp(input) - exp(-input)) / (exp(input) + exp(-input)));

#else

    return 0.0;

#endif
}

void decoderesults(result_s* inputresults) {
    float* largest_ptr = max_element(inputresults->results, inputresults->results + 6);
    int index = distance(inputresults->results, largest_ptr);
    cout << "\nHighest confidence is " << *largest_ptr << " at index " << index << "\n\n";
    inputresults->axis = result_axis[index];
}
