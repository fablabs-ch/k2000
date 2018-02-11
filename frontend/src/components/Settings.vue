<template>
  <v-container fluid>
    <v-layout column justify-space-around>
      <v-flex md6 offset-md3>
      <h3><img src="../assets/ingredients-list.svg" alt="settings"> Setttings</h3>
        <v-card>
          <v-toolbar dark color="primary">
            <v-toolbar-title class="white--text">Debug Commands</v-toolbar-title>
          </v-toolbar>
          <v-card-title>
            <v-layout column justify-space-around>
              <v-list>
                <v-btn color="primary" @click="tare()">Tare</v-btn>
                <v-btn color="error" @click="stop()">Stop</v-btn>

                <v-text-field name="mm" label="mm" v-model="debug.mm" type="number"></v-text-field>
                <v-text-field name="servoId" label="servoId" v-model="debug.servoId" type="text"></v-text-field>
                <v-text-field name="aperture" label="aperture" v-model="debug.aperture" type="number"></v-text-field>

                <v-btn color="warning" @click="move()">Move</v-btn>
                <v-btn color="warning" @click="servo()">Servo</v-btn>
                <v-btn color="warning" @click="fill()">Fill</v-btn>

                <v-text-field name="testMsg" label="Test command" v-model="debug.testMsg" type="text"></v-text-field>

                <v-btn color="warning" @click="testMsg()">Send</v-btn>

              </v-list>
            </v-layout>
          </v-card-title>
        </v-card>

        <v-card>
          <v-toolbar dark color="primary">
            <v-toolbar-title class="white--text">Add New Ingridient Config</v-toolbar-title>
          </v-toolbar>
          <v-card-title>
            <v-layout column justify-space-around>
              <v-list>
                <ingredientConfig :value="newingredientConfig"></ingredientConfig>
              </v-list>
            </v-layout>
          </v-card-title>
          <v-card-actions>
            <v-spacer></v-spacer>
            <v-btn color="primary" @click.native="add" >Add</v-btn>
          </v-card-actions>
        </v-card>

        <v-card>
          <v-list two-line>
            <ingredientConfig :canDelete="true" v-for="item in config" :value='item' @change="save"  @delete="deleteItem" :key="item.id"></ingredientConfig>
          </v-list>
       </v-card>
      </v-flex>
    </v-layout>
  </v-container>
</template>

<script>
import IngredientConfig from '@/components/ingredientConfig'

export default {
  name: 'settings',
  components: {
    IngredientConfig
  },
  data () {
    return {
      newingredientConfig: this.createNewingredientConfig(),
      config: [],
      debug: {
        mm: 0,
        servoId: '',
        aperture: 0,
        testMsg: ''
      }
    }
  },
  methods: {
    createNewingredientConfig () {
      return {
        ingredientId: null,
        valveDistanceMm: 0,
        valveId: 0
      }
    },
    add () {
      this.$http.post('config', this.newingredientConfig).then(reponse => {
        const savedingredientConfig = reponse.data
        this.config.push(savedingredientConfig)
        this.newingredientConfig = this.createNewingredientConfig()
      })
    },
    save (ingredientConfig) {
      this.$http.put(`config/${ingredientConfig.id}`, ingredientConfig).then(reponse => {
        this.$root.notify('Saved!')
      })
    },
    deleteItem (ingredientConfig) {
      this.$http.delete(`config/${ingredientConfig.id}`, ingredientConfig).then(reponse => {
        this.$delete(this.config, this.config.indexOf(ingredientConfig))
      })
    },
    tare () {
      this.$http.get('debug/tare').then(response => {
        this.$root.notify('Tare sent')
      }, response => {
        this.$root.notify('Error when trying to tare')
      })
    },
    stop () {
      this.$http.get('command/stop').then(response => {
        this.$root.notify('Stop sent')
      }, response => {
        this.$root.notify('Error when trying to stop')
      })
    },
    move () {
      this.$http.get(`debug/move/${this.debug.mm}`).then(response => {
        this.$root.notify('Move sent')
      }, response => {
        this.$root.notify('Error with move command')
      })
    },
    servo () {
      this.$http.get(`debug/servo/${this.debug.servoId}/${this.debug.aperture}`).then(response => {
        this.$root.notify('Servo sent')
      }, response => {
        this.$root.notify('Error with servo command')
      })
    },
    fill () {
      this.$http.get(`debug/fill/${this.debug.mm}/${this.debug.servoId}/${this.debug.aperture}`).then(response => {
        this.$root.notify('Fill sent')
      }, response => {
        this.$root.notify('Error with fill command')
      })
    },
    testMsg () {
      this.$http.get(`debug/test/${this.debug.testMsg}`).then(response => {
        this.$root.notify('Test message sent')
      }, response => {
        this.$root.notify('Error with test message')
      })
    }
  },
  mounted () {
    this.$http.get('config').then(response => {
      this.config = response.data || []
    }, response => {
      this.$root.notify('Impossible to load the config')
    })
  }
}
</script>

<style>

</style>

