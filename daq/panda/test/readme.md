### Documentation for testScript.py
testScript.py runs the main.py script but limited to num_runs.

### Documentation for blackbox
The 'blackbox' stores a local copy of the trial data for each run, so that we are never at risk of losing this data in the case of an internet or firebase outage.
The interpreter uploads this data to the firebase to replace the missing trial.
