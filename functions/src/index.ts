import * as functions from 'firebase-functions';
import * as admin from 'firebase-admin';
const fibonacci = require('fibonacci');

admin.initializeApp();

// // Start writing Firebase Functions
// // https://firebase.google.com/docs/functions/typescript
export const helloWorld = functions.https.onRequest((request, response) => {
    functions.logger.info("Hello logs!", {structuredData: true});
    response.send("Hello from Firebase!");
});

/**
 * Get a nice customized greeting from the server!
 */
export const getGreeting = functions.https.onRequest((request, response) => {
    const name = request.query.name;
    response.send({
        name: name,
        greeting: `Hello ${name}!`
    });
})

export const changeData = functions.https.onRequest(async (req, res) => {
    const docRef = admin.firestore().collection('Sensors').doc('sensor1');
    await docRef.get().then(async (snapshot) => {
        const data = snapshot.data();
        if (!data) {
            // Handle error
            res.send({ error: 'sensor1 data is undefined' });
            return;
        }
        const oldValue = data['value'];
        const fibonacciNumber = fibonacci.iterate(req.body.num).number;
        await docRef.update({ value: fibonacciNumber });
        res.send({
            'oldValue': oldValue,
            'currentValue': fibonacciNumber
        });
    }).catch(error => res.status(500).send({ error: error }))
});
