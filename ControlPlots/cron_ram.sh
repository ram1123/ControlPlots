while true; do
    echo "Running git add, commit and push"
    git -C /afs/cern.ch/user/r/rasharma/work/nanoAODToolDev_H4l/plotting/ControlPlots/ControlPlots add . 
    git -C /afs/cern.ch/user/r/rasharma/work/nanoAODToolDev_H4l/plotting/ControlPlots/ControlPlots commit -m "Updated CSV using cron jobs"
    git -C /afs/cern.ch/user/r/rasharma/work/nanoAODToolDev_H4l/plotting/ControlPlots/ControlPlots push origin Anusreevijay769-dev_HZZ_2l2q 
    sleep 60  # Sleeps for 14400 seconds or 4 hours
done

