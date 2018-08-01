{
   TCanvas *c1 = new TCanvas("c1", "c1",15,49,1051,500);

   Int_t numchains=6;

   Double_t chain[6];
   Double_t chainerr[6];

   for (Int_t i=0;i<numchains;i++){
      chain[i]=i;
      chainerr[i]=0.0;
   };

   Double_t ram[6] = {
      0.15,
      0.165,
      0.176,
      0.195,
      0.227,
      0.287
   };

   Double_t l2timerms[6] = {
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0
   };

   std::string names[6] = {
      "inf",
      "5000",
      "4500",
      "4000",
      "3500",
      "3000"
   };

   TGraphErrors *l2timevschain = new TGraphErrors(numchains,chain,ram,chainerr,l2timerms);
   TAxis *ax = l2timevschain->GetHistogram()->GetXaxis();
   Double_t x1 = ax->GetBinLowEdge(1);
   Double_t x2 = ax->GetBinUpEdge(ax->GetNbins());
   l2timevschain->GetHistogram()->GetXaxis()->Set(numchains,x1,x2);

   for(Int_t k=0;k<numchains;k++){
      l2timevschain->GetHistogram()->GetXaxis()->SetBinLabel(k+1,names[k].c_str());
   }

   l2timevschain->SetMarkerStyle(21);
   //l2timevschain->Draw("AP");




   Double_t ram2[6] = {
      -0.15,
      -0.165,
      -0.176,
      -0.195,
      -0.227,
      -0.287
   };

   Double_t l2timerms2[6] = {
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0
   };

   //std::string names[6] = {
   //   "inf",
   //   "5000",
   //   "4500",
   //   "4000",
   //   "3500",
   //   "3000"
   //};

   TGraphErrors *l2timevschain2 = new TGraphErrors(numchains,chain,ram2,chainerr,l2timerms2);
   TAxis *ax1 = l2timevschain2->GetHistogram()->GetXaxis();
   x1 = ax1->GetBinLowEdge(1);
   x2 = ax1->GetBinUpEdge(ax1->GetNbins());
   l2timevschain2->GetHistogram()->GetXaxis()->Set(numchains,x1,x2);

   for(Int_t k=0;k<numchains;k++){
      l2timevschain2->GetHistogram()->GetXaxis()->SetBinLabel(k+1,names[k].c_str());
   }

   l2timevschain2->SetMarkerStyle(21);
   //l2timevschain2->Draw("AP");


   TMultiGraph *mg = new TMultiGraph();
   mg->Add(l2timevschain);
   mg->Add(l2timevschain2);

   mg->Draw("AP");

}
