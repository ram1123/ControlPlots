#ifndef WVCHANNEL_GETCARD_WITHHIGGSDISTRIBUTIONS_H
#define WVCHANNEL_GETCARD_WITHHIGGSDISTRIBUTIONS_H

typedef struct SampleInfo_t {
    int     index;
    TString samplename;
    TString treefilename;
    double xsecpblumi;
    double otherscale;
    int    nMCevents;
    int    MCnegEvent;
    int    colorcode;
    int    stackit;
}
SampleInfo_t;
using namespace std;

double intLUMIinvpb;

double fs0[] = {-50.0, -45.0, -40.0, -35.0, -30.0, -20.0, -10.0, -8.0, -6.0, -5.0, -4.0, -3.0, -2.5, -2.0, -1.5, -1.2, -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 20.0, 30.0, 35.0, 40.0, 45.0, 50.0};
double fs1[] = {-35, -33, -30, -25, -20, -15, -10, -7.5, -5.0, -4.0, -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0, 7.5, 10, 15, 20, 25, 30, 33, 35};
double fm0[] = {-10, -9, -8, -7, -6, -5, -4, -3, -2.0, -1.5, -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.5, 2.0, 3, 4, 5, 6, 7, 8, 9, 10};
double fm1[] = {-30, -28, -23, -21, -18, -15, -13, -10, -5.0, -3.0, -2.5, -2.1, -1.8, -1.5, -1.2, -0.9, -0.6, -0.3, 0, 0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 2.5, 3.0, 5.0, 10, 13, 15, 18, 21, 23.0, 28, 30};
double fm2[] = {-60.0, -55.0, -50.0, -45.0, -40.0, -35.0, -30.0, -25.0, -20.0, -15.0, -10.0, -6.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 6.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0};
double fm3[] = {-105.0, -95.0, - 85.0, -75.0, -65.0, -55.0, -44.0, -31.0, -21.0, -13.0, -8.0, -5.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 5.0, 8.0, 13.0, 21.0, 31.0, 44.0, 55.0, 65.0, 75.0, 85.0, 95.0, 105.0};
double fm4[] = {-130.0,-121.0,-115.0,105.0,-95.0, -85.0, -75.0, -65.0, -55.0, -44.0, -31.0, -21.0, -13.0, -8.0, -5.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 5.0, 8.0, 13.0, 21.0, 31.0, 44.0, 55.0, 65.0, 75.0, 85.0, 95.0, 105.0, 115.0, 121.0, 130.0};
double fm5[] = {-200.0, -190.0, -170.0, -150.0, -130.0,-121.0,-115.0,105.0,-95.0, -85.0, -75.0, -65.0, -55.0, -44.0, -31.0, -21.0, -13.0, -8.0, -5.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 5.0, 8.0, 13.0, 21.0, 31.0, 44.0, 55.0, 65.0, 75.0, 85.0, 95.0, 105.0, 115.0, 121.0, 130.0, 150.0, 170.0, 190.0, 200.0};
double fm6[] = {-20.0, -18.0, -15.0,- -12.0, -10.0, -7.0, -5.0, -3.0, -2.0, -1.8, -1.6, -1.4, -1.2, -1.0, -0.7, -0.5, -0.2, 0.0, 0.2, 0.5, 0.7, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 3.0, 5.0, 7.0, 10.0, 12.0, 15.0, 18.0, 20.0};
double fm7[] = {-40, -35, -30, -25, -20, -15, -10, -5.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0};
double ft0[] = {-2.0, -1.8, -1.4, -1.2, -1.0, -0.7, -0.5, -0.3, -0.2, -0.18, -0.14, -0.12, -0.10, -0.08, -0.06, -0.04, -0.02, 0, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.18, 0.20, 0.30, 0.50, 0.7, 1.0, 1.2, 1.4, 1.8, 2.0};
double ft1[] = {-2.0, -1.8, -1.4, -1.2, -1.0, -0.7, -0.5, -0.3, -0.2, -0.18, -0.14, -0.12, -0.10, -0.08, -0.06, -0.04, -0.02, 0, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.18, 0.20, 0.30, 0.50, 0.7, 1.0, 1.2, 1.4, 1.8, 2.0};
double ft2[] = {-4.5, -3.9, -3.4, -2.9, -2.5, -1.7, -1.2, -0.9, -0.7, -0.5, -0.32, -0.26, -0.20, -0.14, -0.08, -0.04, -0.02, 0, 0.02, 0.04, 0.08, 0.14, 0.20, 0.26, 0.32, 0.5, 0.7, 0.9, 1.2, 1.7, 2.5, 2.9, 3.4, 3.9, 4.5};
double ft5[] = {-25.0, -22.0, -20.0, -18.0, -15.0, -12.0, -10.0, -7.0, -5.0, -3.0, -2.0, -1.8, -1.6, -1.4, -1.2, -1.0, -0.7, -0.5, -0.2, 0.0, 0.2, 0.5, 0.7, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 3.0, 5.0, 7.0, 10.0, 12.0, 15.0, 18.0, 20.0, 22.0, 25.0};
double ft6[] = {-29.0, -27.0, -25.0, -22.0, -20.0, -18.0, -15.0, -12.0, -10.0, -7.0, -5.0, -3.0, -2.0, -1.8, -1.6, -1.4, -1.2, -1.0, -0.7, -0.5, -0.2, 0.0, 0.2, 0.5, 0.7, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 3.0, 5.0, 7.0, 10.0, 12.0, 15.0, 18.0, 20.0, 22.0, 25.0, 27.0, 29.0};
double ft7[] = {-70.0, -65.0, -60.0, -55.0, -50.0, -45.0, -40.0, -35.0, -30.0, -20.0, -10.0, -8.0, -6.0, -5.0, -4.0, -3.0, -2.5, -2.0, -1.5, -1.2, -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 8.0, 10.0, 20.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0};
double ft8[] = {-2.0, -1.8, -1.4, -1.2, -1.0, -0.7, -0.5, -0.3, -0.2, -0.18, -0.14, -0.12, -0.10, -0.08, -0.06, -0.04, -0.02, 0, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.18, 0.20, 0.30, 0.50, 0.7, 1.0, 1.2, 1.4, 1.8, 2.0};
double ft9[] = {-10.0, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};

//======================================================================
class Sample {
public:
    Sample(const SampleInfo_t& sinfo) {
        info_ = sinfo;
        tree_ = 0;
        th1f_ = 0;
        //cout << "sample = " << name_ << endl;
        TFile *f = new TFile (sinfo.treefilename, "READ"); if (!f) { cerr << "Couldn't find file " << sinfo.treefilename << endl; return; }
        // TFile *f =  TFile::Open("root://cmsxrootd.fnal.gov/"+sinfo.treefilename, "READ"); if (!f) { cerr << "Couldn't find file " << sinfo.treefilename << endl; return; }
        tree_ =  (TTree *)f->Get("Events"); if (!tree_) { cerr << "Couldn't find tree otree in file " << sinfo.treefilename << endl; return; }
        if (!(sinfo.samplename=="data")) th1f_ = (TH1F *)f->Get("TotalEvents"); if (!th1f_) {cerr << "Couldn't find TotalEvents in the file " << sinfo.treefilename << endl; return;}
    }
    ~Sample() { if (tree_) delete tree_; }
    TTree *Tree() const { return tree_; }
    TH1F *TInputHist() const {return th1f_; }
    TString name() const { return info_.samplename; }
    TString filename() const { return info_.treefilename; }
    bool stackit() const { return (info_.stackit != 0); }
    int colorcode() const { return info_.colorcode; }
    double otherscale() const { return info_.otherscale; }
    double cross() const {return info_.xsecpblumi; }
    int mcevent() const {return info_.nMCevents; }
    int mcevent_neg() const {return info_.MCnegEvent; }
private:
    SampleInfo_t info_;
    TTree *tree_;
    TH1F *th1f_;
};

//======================================================================
//
void loadSamples(const char *filename,vector<Sample *>& samples)
{
    FILE *fp = fopen(filename,"r");
    if (!fp) {
        cout << "Error, file " << TString(filename) << " not found." << endl;
        exit(-1);
    }
    
    char line[512];
    
    intLUMIinvpb=-1; // obvious error condition
    
    for (int i=0; !feof(fp) && fgets(line,512,fp); i++) {
        if (!strlen(line) || line[0]=='#') continue; // comments are welcome
        
        string strline(line);
        strline.pop_back();     // shed the \n
        vector<string> fields;
        
        // expect columns with fields cutname, cutvalue, possible embedded spaces both
        // within and between, so " " or "\t" cannot be used as delimiters. Require quotes
        // instead.
        //
        Tokenize(strline,fields, " \t");
        
        //for (size_t j=0; j<fields.size(); j++)
        //cout << j << ": \"" << fields[j] << "\"" << endl;
        
        assert (fields.size()==8);
        
        SampleInfo_t s;
        s.index        = i;
        s.samplename   = fields[0];
        s.treefilename = fields[1];
        s.xsecpblumi   = str2dbl(fields[2]);
        s.otherscale   = str2dbl(fields[3]);
        s.nMCevents    = str2int(fields[4]);
        s.MCnegEvent   = str2int(fields[5]);
        s.colorcode    = str2int(fields[6]);
        s.stackit      = str2int(fields[7]);
        
        //if (!s.samplename.EqualTo("aQGC")) continue;
        
        cout << "Loading sample " << s.samplename << " -> " << s.treefilename << endl;
        
        
        if (!samples.size()) {
            if (s.samplename.EqualTo("data")) {
                intLUMIinvpb = s.xsecpblumi;
                s.xsecpblumi = 1;
                cout << "intLUMI = " << intLUMIinvpb << " pb^-1" << endl;
            } else {
                cerr << "First sample in the table must be 'data'" << endl;
                //exit(-1);
            }
        } else {
            s.otherscale *= intLUMIinvpb;
        }
        
        samples.push_back(new Sample(s) );
    }
}                                                         // loadSamples
//======================================================================

void loadCutString(const char *filename, TString& cutstring)
{
    FILE *fp = fopen(filename,"r");
    if (!fp) {
        cout << "Error, file " << TString(filename) << " not found." << endl;
        exit(-1);
    }
    
    char line[512];
    
    for (int i=0; !feof(fp) && fgets(line,512,fp); i++) {
        if (!strlen(line) || line[0]=='#') continue; // comments are welcome
        
        if (cutstring.Length()) cutstring += " && ";
        
        string strline(line);
        strline.pop_back();     // shed the \n
        vector<string> fields;
        
        // expect columns with fields cutname, cutvalue, possible embedded spaces both
        // within and between, so " " or "\t" cannot be used as delimiters. Require quotes
        // instead.
        //
        Tokenize(strline,fields, "\"");
        
        //for (size_t j=0; j<fields.size(); j++)
        //cout << j << ": \"" << fields[j] << "\"" << endl;
        
        assert (fields.size()==3);
        cutstring += TString(fields.at(2));
    }
}                                                       // loadCutString

#endif
