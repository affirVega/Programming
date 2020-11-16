import json

with open('in.json', 'r') as f:
    j = json.load(f)

out = []

for task in j:
    userId    = task['userId']
    completed = task['completed']

    selectedUser = None
    for user in out:
        if user['userId'] == userId:
            selectedUser = user
            break

    if selectedUser == None:
        selectedUser = {}
        selectedUser['userId'] = userId
        selectedUser['task_completed'] = 0
        out.append(selectedUser)

    if completed:
        selectedUser['task_completed'] += 1

print(json.dumps(out, indent=2))

with open('out.json', 'w') as f:
    f.write(json.dumps(out, indent=2))
