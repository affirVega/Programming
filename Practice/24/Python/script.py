import json

with open('in.json', 'r') as f:
    j = json.load(f)

out = []

for task in j:
    userId    = task['userId']
    completed = task['completed']

    # Find user in out with userId
    selectedUser = None
    for user in out:
        if user['userId'] == userId:
            selectedUser = user
            break

    # If this user was not found, create one
    if selectedUser == None:
        selectedUser = {}
        selectedUser['userId'] = userId
        selectedUser['task_completed'] = 0
        out.append(selectedUser)

    # If task is completed, add one task to completed counter
    if completed:
        selectedUser['task_completed'] += 1

with open('out.json', 'w') as f:
    f.write(json.dumps(out, indent=2))
